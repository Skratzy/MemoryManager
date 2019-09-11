-- premake5.lua
project "MemoryManager"
	kind "StaticLib"
	language "C++"
	
	targetdir (binDir)
	objdir (intermediatesDir)

	files {
		"MemoryManager/src/Allocator.h",
		"MemoryManager/src/MemoryManager.h",
		"MemoryManager/src/Defines.h",
		"MemoryManager/src/PoolAllocator.h",
		"MemoryManager/src/StackAllocator.h",
		"MemoryManager/src/Allocator.cpp",
		"MemoryManager/src/MemoryManager.cpp",
		"MemoryManager/src/PoolAllocator.cpp",
		"MemoryManager/src/StackAllocator.cpp"
	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"
		
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

	filter "configurations:Debug"
		defines { "_DEBUG", "_ITERATOR_DEBUG_LEVEL=2" }
