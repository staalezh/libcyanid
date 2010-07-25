############################################################
# SConstruct file for libcyanid                            #
############################################################

env = Environment()
env["LIBS"] = ["net"]
env["CXXFLAGS"] = "-Wall -g -ggdb"

sources = Split("""
        src/arp.cpp
        src/device.cpp
        src/ethernet.cpp
        src/packet.cpp
        src/utils/convert.cpp
        """)

env.SharedLibrary("cyanid", sources)

env.Install('/usr/lib', 'libcyanid.so')
env.Install('/usr/include/cyanid', Split("""
            src/arp.hpp
            src/builder.hpp
            src/context.hpp
            src/cyanid.hpp
            src/device.hpp
            src/ethernet.hpp
            src/packet.hpp
            src/types.hpp"""))
env.Install('/usr/include/cyanid/utils', Split("""
            src/utils/convert.hpp
            src/utils/smart_ptr.hpp
            """))

env.Alias('install', Split("""
            /usr/lib
            /usr/include/cyanid
            /usr/include/cyanid/utils
            """))
