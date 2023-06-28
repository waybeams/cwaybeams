workspace "Beam"
	configurations { "Debug", "Test", "Release" }
	language "C"
	cdialect "C11"
	toolset "gcc"

	files {
		"include/*.h",
		"src/*.c",
	}

	buildoptions {
		"-Iinclude",
		"-Wall",
		"-Werror",
		"-std=c11",
    -- NOTE(lbayes): -pedantic causes a failure with __VA_ARGS__ GCC only
    -- extension.
    -- "-pedantic",
	}

	libdirs {
		"vendor/gl/include",
		"vendor/glfw/include",
		"vendor/hash",
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

project "beam"
	kind "SharedLib"
	targetdir "dist/%{cfg.buildcfg}"

project "beam-todo-glfw"
	kind "ConsoleApp"
	targetdir "dist/%{cfg.buildcfg}"

	files {
		"src/render/glfw.*",
		"examples/todo/main_todo.c",
	}

	links {
		"glfw",
	}

project "beam-test"
	kind "ConsoleApp"
	targetdir "dist/%{cfg.buildcfg}"

	files {
		"test/*"
	}

