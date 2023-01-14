def _build_html():
    with open("control_fan_driver.html", "r") as f:
        filecontent = f.readlines()

    with open("include/control_page_html.h", "w+") as f:
        f.write("#pragma once\n\n")
        f.write("static const char CONTROL_PAGE_HTML[] ICACHE_RODATA_ATTR =\n")
        for line in filecontent:
            # strip trailing \n, escape quotes
            line = line[:-1].replace('"', '\\"')
            # insert a c-style newline
            f.write('"' + line + '\\r\\n"\n')
        f.write(";\n")


def _build_favicon():
    with open("fan.ico", "rb") as f:
        binaryContent = f.read()

    with open("include/favicon_html.h", "w+") as f:
        f.write("#pragma once\n\n#include<Arduino.h>\n\n")
        f.write(
            "static const byte FAVICON_CONTENT_HTML[] ICACHE_RODATA_ATTR = { \\\n")
        blocksize = 32
        for block in [binaryContent[i:i + blocksize] for i in range(0, len(binaryContent), blocksize)]:
            f.write("\t" + ", ".join(map(lambda b: "0x%02x" % b, block)) + ", \\\n")
        f.write("};\n")


_build_html()
_build_favicon()
