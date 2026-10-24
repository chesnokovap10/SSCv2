// Headless: decompile every function of the current program to <outdir>/<name>.c
// and write <outdir>/_all.c. Run through libssc/research/ghidra/decompile.ps1.
// @category libssc

import java.io.File;
import java.io.PrintWriter;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class DecompileAll extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0] : "decomp");
        out.mkdirs();

        DecompInterface ifc = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        ifc.setOptions(opts);
        ifc.openProgram(currentProgram);

        try (PrintWriter all = new PrintWriter(new File(out, "_all.c"), "UTF-8")) {
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            int n = 0;
            while (it.hasNext() && !monitor.isCancelled()) {
                Function f = it.next();
                if (f.isExternal() || f.isThunk()) {
                    continue;
                }
                DecompileResults r = ifc.decompileFunction(f, 120, monitor);
                String body = (r != null && r.decompileCompleted())
                        ? r.getDecompiledFunction().getC()
                        : "/* decompile failed: " + (r == null ? "null" : r.getErrorMessage()) + " */\n";
                String header = "/* " + f.getName() + " @ " + f.getEntryPoint() + " size "
                        + f.getBody().getNumAddresses() + " */\n";
                try (PrintWriter w = new PrintWriter(new File(out, f.getName() + ".c"), "UTF-8")) {
                    w.print(header);
                    w.print(body);
                }
                all.print(header);
                all.print(body);
                all.print("\n");
                n++;
            }
            println("decompiled " + n + " functions to " + out.getAbsolutePath());
        } finally {
            ifc.dispose();
        }
    }
}
