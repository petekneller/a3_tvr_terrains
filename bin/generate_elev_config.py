#! /bin/env python

import yaml
from jinja2 import Environment, FileSystemLoader

try:
    with open("world_config.yaml", "r") as config_file:
        config = yaml.safe_load(config_file)

        env = Environment(
            loader=FileSystemLoader("src/"),
            keep_trailing_newline=True,
            trim_blocks=True,
            lstrip_blocks=True
        )

        template = env.get_template("CustomHeightmapList.xml.tmpl")
        with open("out/tacview/CustomHeightmapList.xml", "w") as output_file:
            output_file.write(template.render(config=config))

except Exception as exc:
    print(f"Exception raised: {exc}")
