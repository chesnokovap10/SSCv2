package nativebtpackage

import "embed"

// Files contains the signed x64 test driver and its public signing certificate.
//
//go:embed local-package/SscAvdtpLocal.inf local-package/SscAvdtpLocal.sys local-package/sscavdtplocal.cat local-package/signer.cer
var Files embed.FS
