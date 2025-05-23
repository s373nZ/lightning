reckless -- Issue a command to the reckless plugin manager utility
==================================================================

SYNOPSIS
--------

**reckless** *command* [*target/subcommand*] [*target*] 

DESCRIPTION
-----------

The **reckless** RPC starts a reckless process with the *command* and *target* provided.  Node configuration, network, and lightning direrctory are automatically passed to the reckless utility.

- **command** (string) (one of "install", "uninstall", "search", "enable", "disable", "source", "--version"): Determines which command to pass to reckless
   - *command* **install** takes a *plugin\_name* to search for and install a named plugin.
   - *command* **uninstall** takes a *plugin\_name* and attempts to uninstall a plugin of the same name.
   - *command* **search** takes a *plugin\_name* to search for a named plugin.
 ...
- **target/subcommand** (one of, optional): Target of a reckless command or a subcommand.:
  - (string)
  - (array)
- **target** (one of, optional): *name* of a plugin to install/uninstall/search/enable/disable or source to add/remove.:
  - (string)
  - (array)

NOTES
-----

Reckless currently supports python and javascript plugins.
Running the first time will prompt the user that their lightningd's bitcoin config will be appended (or created) to inherit the reckless config file (this config is specific to bitcoin by default.). Management of plugins will subsequently modify this file.

Available option flags:
**-d**, **--reckless-dir** *reckless\_dir*: specify an alternative data directory for reckless to use. Useful if your .lightning is protected from execution.

**-l**, **--lightning** *lightning\_data\_dir*: lightning data directory (defaults to $USER/.lightning)

**-c**, **--conf** *lightning\_config*: pass the config used by lightningd

**-r**, **--regtest**: use the regtest network and config instead of bitcoin mainnet

**-v**, **--verbose**: request additional debug output

**--network**=*network*: specify bitcoin, regtest, liquid, liquid-regtest, litecoin, signet, or testnet networks. (default: bitcoin)

**--version**: print the version of reckless and exit


Troubleshooting tips:

Plugins must be executable. For python plugins, the shebang is invoked, so **python3** should be available in your environment. This can be verified with **which Python3**. The default reckless directory is $USER/.lightning/reckless and it should be possible for the lightningd user to execute files located here. If this is a problem, the option flag **reckless -d=<my\_alternate\_dir>** may be used to relocate the reckless directory from its default. Consider creating a permanent alias in this case.
Python plugins are installed to their own virtual environments. The environment is activated by a wrapper (named the same as the plugin) which then imports and executes the actual plugin entrypoint.

For Plugin Developers:

To make your plugin compatible with reckless install:
- Choose a unique plugin name: The plugin entrypoint is inferred. Naming your plugin executable the same as your plugin name will allow reckless to identify it correctly (file extensions are okay.)
- For python plugins, a requirements.txt is the preferred medium for python dependencies. A pyproject.toml will be used as a fallback, but test installation via `pip install -e .` - Poetry looks for additional files in the working directory, whereas with pip, any references to these will require something like `packages = [{ include = "*.py" }]` under the `[tool.poetry]` section.
- Additional repository sources may be added with `reckless source add https://my.repo.url/here` however, https://github.com/lightningd/plugins is included by default. Consider adding your plugin lightningd/plugins to make installation simpler.
- If your plugin is located in a subdirectory of your repo with a different name than your plugin, it will likely be overlooked.

RETURN VALUE
------------

On success, an object is returned, containing:

- **result** (array of strings): Output of the requested reckless command.:
  - (string, optional)
- **log** (array of strings): Verbose log entries of the requested reckless command.:
  - (string, optional)

AUTHOR
------

Antoine Poinsot wrote the original reckless plugin on which this is based.

Rusty Russell wrote the outline for the reckless utility's function

Alex Myers <<alex@endothermic.dev>> is mainly responsible for the reckless code and this man page, with thanks to Christian Decker for extensive review.

SEE ALSO
--------

reckless(7)

RESOURCES
---------

Core-Lightning plugins repo: <https://github.com/lightningd/plugins>
Main web site: <https://github.com/ElementsProject/lightning>

EXAMPLES
--------


**Example 1**: 

Request:
```shell
lightning-cli reckless -k "command"="search" "target/subcommand"="backup"
```
```json
{
  "id": "example:reckless#1",
  "method": "reckless",
  "params": {
    "command": "search",
    "target/subcommand": "backup"
  }
}
```

Response:
```json
{
  "result": [
    "https://github.com/lightningd/plugins"
  ],
  "log": [
    "DEBUG: Warning: Reckless requires write access",
    "DEBUG: fetching from gh API: https://api.github.com/repos/lightningd/plugins/contents/",
    "DEBUG: fetching from gh API: https://api.github.com/repos/lightningd/plugins/git/trees/294f93d7060799439c994daa84f534c4d1458325",
    "INFO: found backup in source: https://github.com/lightningd/plugins",
    "DEBUG: entry: None",
    "DEBUG: sub-directory: backup"
  ]
}
```

**Example 2**: 

Request:
```shell
lightning-cli reckless -k "command"="install" "target/subcommand"='["summars", "currecyrate"]'
```
```json
{
  "id": "example:reckless#2",
  "method": "reckless",
  "params": {
    "command": "install",
    "target/subcommand": [
      "summars",
      "currecyrate"
    ]
  }
}
```

Response:
```json
{
  "result": [
    "/tmp/l1/reckless/summars",
    "/tmp/l1/reckless/currencyrate"
  ],
  "log": [
    "DEBUG: Searching for summars",
    "DEBUG: fetching from gh API: https://api.github.com/repos/lightningd/plugins/contents/",
    "DEBUG: fetching from gh API: https://api.github.com/repos/lightningd/plugins/git/trees/294f93d7060799439c994daa84f534c4d1458325",
    "INFO: found summars in source: https://github.com/lightningd/plugins",
    "DEBUG: entry: None",
    "DEBUG: sub-directory: summars",
    "DEBUG: Retrieving summars from https://github.com/lightningd/plugins",
    "DEBUG: Install requested from InstInfo(summars, https://github.com/lightningd/plugins, None, None, None, summars).",
    "INFO: cloning Source.GITHUB_REPO InstInfo(summars, https://github.com/lightningd/plugins, None, None, None, summars)",
    "DEBUG: cloned_src: InstInfo(summars, /tmp/reckless-726255950dyifh_fh/clone, None, Cargo.toml, Cargo.toml, summars/summars)",
    "DEBUG: using latest commit of default branch",
    "DEBUG: checked out HEAD: 5e449468bd57db7d0f33178fe0dc867e0da94133",
    "DEBUG: using installer rust",
    "DEBUG: creating /tmp/l1/reckless/summars",
    "DEBUG: creating /tmp/l1/reckless/summars/source",
    "DEBUG: copying /tmp/reckless-726255950dyifh_fh/clone/summars/summars tree to /tmp/l1/reckless/summars/source/summars",
    "DEBUG: linking source /tmp/l1/reckless/summars/source/summars/Cargo.toml to /tmp/l1/reckless/summars/Cargo.toml",
    "DEBUG: InstInfo(summars, /tmp/l1/reckless/summars, None, Cargo.toml, Cargo.toml, source/summars)",
    "DEBUG: cargo installing from /tmp/l1/reckless/summars/source/summars",
    "DEBUG: rust project compiled successfully",
    "INFO: plugin installed: /tmp/l1/reckless/summars",
    "DEBUG: activating summars",
    "INFO: summars enabled",
    "DEBUG: Searching for currencyrate",
    "DEBUG: fetching from gh API: https://api.github.com/repos/lightningd/plugins/contents/",
    "DEBUG: fetching from gh API: https://api.github.com/repos/lightningd/plugins/git/trees/294f93d7060799439c994daa84f534c4d1458325",
    "INFO: found currencyrate in source: https://github.com/lightningd/plugins",
    "DEBUG: entry: None",
    "DEBUG: sub-directory: currencyrate",
    "DEBUG: Retrieving currencyrate from https://github.com/lightningd/plugins",
    "DEBUG: Install requested from InstInfo(currencyrate, https://github.com/lightningd/plugins, None, None, None, currencyrate).",
    "INFO: cloning Source.GITHUB_REPO InstInfo(currencyrate, https://github.com/lightningd/plugins, None, None, None, currencyrate)",
    "DEBUG: cloned_src: InstInfo(currencyrate, /tmp/reckless-192564272t478naxn/clone, None, currencyrate.py, requirements.txt, currencyrate/currencyrate)",
    "DEBUG: using latest commit of default branch",
    "DEBUG: checked out HEAD: 5e449468bd57db7d0f33178fe0dc867e0da94133",
    "DEBUG: using installer python3venv",
    "DEBUG: creating /tmp/l1/reckless/currencyrate",
    "DEBUG: creating /tmp/l1/reckless/currencyrate/source",
    "DEBUG: copying /tmp/reckless-192564272t478naxn/clone/currencyrate/currencyrate tree to /tmp/l1/reckless/currencyrate/source/currencyrate",
    "DEBUG: linking source /tmp/l1/reckless/currencyrate/source/currencyrate/currencyrate.py to /tmp/l1/reckless/currencyrate/currencyrate.py",
    "DEBUG: InstInfo(currencyrate, /tmp/l1/reckless/currencyrate, None, currencyrate.py, requirements.txt, source/currencyrate)",
    "DEBUG: configuring a python virtual environment (pip) in /tmp/l1/reckless/currencyrate/.venv",
    "DEBUG: virtual environment created in /tmp/l1/reckless/currencyrate/.venv.",
    "INFO: dependencies installed successfully",
    "DEBUG: virtual environment for cloned plugin: .venv",
    "INFO: plugin installed: /tmp/l1/reckless/currencyrate",
    "DEBUG: activating currencyrate",
    "INFO: currencyrate enabled"
  ]
}
```
