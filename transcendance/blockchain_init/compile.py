import subprocess

registry = ["docker","run","-v","./:/sources","ethereum/solc:0.8.24","-o","/sources/output/registry","--abi","--bin","--overwrite","/sources/Registry.sol"]
tournament = ["docker","run","-v","./:/sources","ethereum/solc:0.8.24","-o","/sources/output/tournament","--abi","--bin","--overwrite","/sources/Tournament.sol"]

subprocess.run(registry)
subprocess.run(tournament)
