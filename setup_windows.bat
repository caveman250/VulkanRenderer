mkdir vs_project
cd vs_project
cmake -DCMAKE_BUILD_TYPE=Debug -DASSIMP_BUILD_ASSIMP_TOOLS=false -DASSIMP_BUILD_TESTS=false -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=false -DASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT=false -DASSIMP_BUILD_OBJ_IMPORTER=true -DASSIMP_BUILD_COLLADA_IMPORTER=true -DGLFW_BUILD_DOCS=false -DGLFW_BUILD_EXAMPLES=false -DGLFW_BUILD_TESTS=false -DGLFW_INSTALL=false ..