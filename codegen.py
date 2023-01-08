with open("control_fan_driver.html", "r") as f:
    filecontent = f.readlines()

with open("include/control_page_html.h", "w+") as f:
    f.write("#pragma once\n")
    f.write("const char * CONTROL_PAGE_HTML =\n")
    for line in filecontent:
        # strip trailing \n, escape \"
        line = line[:-1].replace('"', '\\"')
        f.write('"' + line + '"\n')
    f.write(";\n")
