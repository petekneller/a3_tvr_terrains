So you've got a terrain that you've got working in Tacview through the process I documented in [adding new terrain](adding_content.md) and you'd like to have it added to this repo so that others can use it easily? Wonderful. Thanks!

There's nothing special about contributing to this repo than any other, if you've opened pull requests before. If you haven't this might be a little confusing and daunting. Github has a [tutorial](https://docs.github.com/en/get-started/exploring-projects-on-github/contributing-to-a-project) on the important concepts and steps to get you started. Once you're comfortable with the process and happy with the terrain you're prepared then just open a pull request. I'll be notified and (hopefully) get back to you reasonably quickly. I've added a little checklist below of the sort of things I'll be looking for in the addition:

1. world_config.yaml
   1. The terrain's got a unique, sensible name that broadly reflects what it is
   2. It's located somewhere broadly sensible on the globe and its more or less a square shape
   3. It's correctly attributed to the authors. You probaby ignored the author fields in the config file (as I suggested) when setting up the terrain. You'll need to fill them out now. The `steam` section of the config should refer to the source of the terrain itself and the `owner` section the authors. The `name` field of each of those should be the published name of the mod and the author respectively. And `workshop` the URL of the mod and the author's profile page. Where the author is a cDLC team I've used the URL for the cDLC itself. If in doubt have a look at some examples of other terrains and how I've managed them.
2. Terrain image and elevation data: these should both be in the `src/` folder with the correct names.
