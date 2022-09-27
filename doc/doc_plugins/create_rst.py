from pathlib import Path
from configparser import ConfigParser

import subprocess
import os


def create_file(file, p):

    with file.open() as infile:
        lines =infile.readlines()
        if any([line in ["//NoDocsPage\n", "//NoDocsPage", "// NoDocsPage\n", "// NoDocsPage"] for line in lines] ):
            print(f"nodocspage  as {file}")
            return

    relp = Path(os.path.relpath(file, p))

    of = Path("api") / relp.parent / f"{file.stem}_gen.rst"

    if not of.parent.exists():
        new_index = Path(str(of.parent) + "_gen.rst")
        print(f"new index at{new_index}")
        if not new_index.is_file():
            if not of.parent.parent.exists():
                of.parent.parent.mkdir(parents=True, exist_ok=True)

            with new_index.open("w") as out:
                fname = of.parent.stem.replace("_", " ").title()
                out.write(f"{fname}\n{'='*len(fname)}\n")
        with new_index.open("a") as out:
            out.write(
                f"\n.. toctree::\n   :maxdepth: 1\n   :caption: Contents:\n   :glob:\n\n   \n   {of.parent.stem}/*\n"
            )
        of.parent.mkdir(parents=True, exist_ok=True)

    if not (Path("api") / relp.parent / f"{file.stem}.rst").is_file():
        with of.open("w") as out:
            fname = file.stem.replace("_", " ").title()
            out.write(f"{fname}\n{'='*len(fname)}\n.. doxygenfile:: {relp}\n\n")

def setup(app):
    subprocess.call("doxygen", shell=True)

    config = ConfigParser()
    with open("Doxyfile") as stream:
        config.read_string("[top]\n" + stream.read())

    files = []
    for input_src in config["top"]["INPUT"].split():
        p = Path(input_src)

        for file in p.glob("**/*.hpp"):
            rel_path = os.path.relpath(file, p)
            print(rel_path)
            files.append((rel_path.count("/"), file, p))
    files.sort(reverse=True)

    while files:
        w, file, parent = files.pop()
        create_file(file, parent)
