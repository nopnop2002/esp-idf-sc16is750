set(component_srcs "sc16is750.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS ".")
