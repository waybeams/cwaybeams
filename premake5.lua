workspace "Beam"
	configurations { "Debug", "Test", "Release" }
	language "C"
	cdialect "C11"

	files {
		"include/*.h",
		"src/*.c",
	}

	buildoptions {
		"-Iinclude",
		"-Ivendor/hash",
	}

	libdirs {
		"vendor/gl/include",
		"vendor/glfw/include",
	}

project "todo-glfw"
	kind "ConsoleApp"
	language "C"
	targetdir "dist/%{cfg.buildcgf}"
	cdialect "C11"

	files {
		"src/render/glfw.*",
		"examples/todo/main_todo.c",
	}

	links {
		"glfw",
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Test"
		defines { "TEST" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

