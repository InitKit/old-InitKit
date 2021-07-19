m4_define(SD_ENTRY,`$1: {
        "priority": $2,
        "command": "'CMAKE_INSTALL_PREFIX/IK_PKG_LIBEXECDIR`/sd_import $`'entryname",
        "desc": $3
    }')m4_dnl
{
    SD_ENTRY("/etc/systemd/system.control", 20,
        "(SystemD) Persistent configuration created using the dbus API"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/system.control", 40,
        "(SystemD) Transient configuration created using the dbus API"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/transient", 60,
        "(SystemD) Dynamic configuration for transient units"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/generator.early", 80,
        "(SystemD) Generated units with high priority (see early-dir in systemd.generator(7))"),
    SD_ENTRY("/etc/systemd/system", 100,
        "(SystemD) System units created by the administrator"),
    SD_ENTRY("/etc/systemd/system.attached", 120,
        "(SystemD) Attached system units created by the administrator"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/system", 140,
        "(SystemD) Runtime units"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/system.attached", 160,
        "(SystemD) Attached runtime units"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/generator", 180,
        "(SystemD) Generated units with medium priority (see normal-dir in systemd.generator(7))"),
    SD_ENTRY("/usr/local/lib/systemd/system", 200,
        "(SystemD) System units installed by the administrator"),
    SD_ENTRY("/usr/local/lib/systemd/system", 220,
        "(SystemD) System units installed by the administrator"),
    SD_ENTRY("/usr/lib/systemd/system", 240,
        "(SystemD) System units installed by the distribution package manager"),
    SD_ENTRY("DEFAULT_RUNSTATE_DIR/systemd/generator.late", 260,
        "(SystemD) Generated units with low priority (see late-dir in systemd.generator(7))")
}
