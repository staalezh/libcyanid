############################################################
# SConstruct file for libcyanid                            #
############################################################

env = Environment()
env["LIBS"] = ["net"]
env["CXXFLAGS"] = "-Wall -g -ggdb"

sources = Split("""
        src/builder/arp.cpp
        src/builder/ethernet.cpp
        src/builder/ip.cpp
        src/device.cpp
        src/listener.cpp
        src/packet.cpp
        src/utils/convert.cpp
        """)

env.SharedLibrary("cyanid", sources)

env.Install('/usr/lib', 'libcyanid.so')

env.Install('/usr/include/cyanid', Split("""
            src/device.hpp
            src/context.hpp
            src/cyanid.hpp
            src/listener.hpp
            src/packet.hpp
            src/raw_packet.hpp
            src/types.hpp"""))

env.Install('/usr/include/cyanid/builder', Split("""
            src/builder/arp.hpp
            src/builder/builder.hpp
            src/builder/ethernet.hpp
            src/builder/ip.hpp
            """))

env.Install('/usr/include/cyanid/utils', Split("""
            src/utils/convert.hpp
            src/utils/smart_ptr.hpp
            """))

env.Alias('install', Split("""
            /usr/lib
            /usr/include/cyanid
            /usr/include/cyanid/builder
            /usr/include/cyanid/utils
            """))
