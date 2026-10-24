// Headless: decompile every function that references a string containing
// "ssc" (any case), plus their direct callees, to <outdir>/. For the stripped
// libbluetooth_jni.so, where the log strings carry the function names.
// Run through libssc/research/ghidra/decompile_bt.ps1.
// @category libssc

import java.io.File;
import java.io.PrintWriter;
import java.util.*;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.Reference;

public class DecompileSsc extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0] : "decomp_bt");
        out.mkdirs();
        Memory mem = currentProgram.getMemory();
        MemoryBlock ro = mem.getBlock(".rodata");
        byte[] buf = new byte[(int) ro.getSize()];
        ro.getBytes(ro.getStart(), buf);

        // strings with "ssc" -> referencing functions
        Map<Function, Set<String>> roots = new TreeMap<>(Comparator.comparing(Function::getEntryPoint));
        int s = 0;
        try (PrintWriter strs = new PrintWriter(new File(out, "_strings.txt"), "UTF-8")) {
            for (int i = 0; i <= buf.length; i++) {
                if (i == buf.length || buf[i] == 0) {
                    if (i - s >= 4) {
                        String str = new String(buf, s, i - s, "ISO-8859-1");
                        if (str.toLowerCase().contains("ssc")) {
                            // references may point anywhere inside the string
                            for (int k = s; k < i; k++) {
                                Address a = ro.getStart().add(k);
                                for (Reference r : getReferencesTo(a)) {
                                    Function f = getFunctionContaining(r.getFromAddress());
                                    strs.println(a + " <- " + r.getFromAddress() + " "
                                            + (f == null ? "?" : f.getName()) + " : " + str);
                                    if (f != null) {
                                        roots.computeIfAbsent(f, x -> new TreeSet<>()).add(str);
                                    }
                                }
                            }
                        }
                    }
                    s = i + 1;
                }
            }
        }
        println("ssc roots: " + roots.size());

        Set<Function> callees = new TreeSet<>(Comparator.comparing(Function::getEntryPoint));
        for (Function f : roots.keySet()) {
            for (Function c : f.getCalledFunctions(monitor)) {
                if (!c.isExternal() && !c.isThunk() && !roots.containsKey(c)) {
                    callees.add(c);
                }
            }
        }

        DecompInterface ifc = new DecompInterface();
        ifc.setOptions(new DecompileOptions());
        ifc.openProgram(currentProgram);
        try (PrintWriter all = new PrintWriter(new File(out, "_roots.c"), "UTF-8");
             PrintWriter cal = new PrintWriter(new File(out, "_callees.c"), "UTF-8")) {
            for (Function f : roots.keySet()) {
                emit(ifc, all, f, String.join(" | ", roots.get(f)));
            }
            for (Function f : callees) {
                if (f.getBody().getNumAddresses() < 4000) {
                    emit(ifc, cal, f, "callee");
                }
            }
        } finally {
            ifc.dispose();
        }
        println("decompiled " + roots.size() + " roots, " + callees.size() + " callees to " + out.getAbsolutePath());
    }

    private void emit(DecompInterface ifc, PrintWriter w, Function f, String tag) {
        DecompileResults r = ifc.decompileFunction(f, 180, monitor);
        String body = (r != null && r.decompileCompleted())
                ? r.getDecompiledFunction().getC()
                : "/* decompile failed */\n";
        w.print("/* ==== " + f.getName() + " @ " + f.getEntryPoint() + " size "
                + f.getBody().getNumAddresses() + " :: " + tag.replace("*/", "* /") + " */\n");
        w.print(body);
        w.print("\n");
        w.flush();
    }
}
