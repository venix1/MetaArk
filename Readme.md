# MetaArk

System for hooking ARK: Survival Evolved server logic to allow additional processing.

Requires MinHook. https://github.com/TsudaKageyu/minhook

Solution is Visual Studio 2015.  Targets Visual Studio 2013 runtime.

Supports Damage modification for APRimalStructure::TakeDamage .  

Currently queries a MongoDB instance to determine if damage is enabled.

Bootstrap your database with this.

use MetaArk
db.createCollection("config")
db.config.insert({"key" : "StructureDamage", "value" : false})

Example Yaml file:
MetaArk.yaml
connectionString: mongodb://localhost:27017
