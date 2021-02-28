# Select pre-compiled package based on target architecture
def skopeo_pkg_arch_map(d):
    arch = d.getVar('TARGET_ARCH', True)
    tune = d.getVar('TUNE_FEATURES', True)
    tune_features = tune.split()
    pkg = None
    if arch == "x86_64":
        if not "mx32" in tune_features:
            pkg = "amd64"
    elif arch == "aarch64" or arch == "arm64":
        pkg = "arm64"

    if pkg is None:
        raise bb.parse.SkipPackage("Target architecture '%s' is not supported by the skopeo layer" %arch)

    return pkg

SKOPEO_PKG_ARCH = "${@skopeo_pkg_arch_map(d)}"