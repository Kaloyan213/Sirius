# Grab all .cfg files in this current directory
file(GLOB CONFIG_FILES "*.cfg")

file(COPY ${CONFIG_FILES}
     DESTINATION ${CMAKE_BINARY_DIR}/Configs)