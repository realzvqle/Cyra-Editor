set_project("editor")
set_languages("c99")

target("editor")
    set_kind("binary")  
    add_files("src/*.c")
    add_files("src/**/*.c") 
    if is_os("windows") then
        --add_cxflags("/fsanitize=address");
        add_linkdirs("lib/windows") 
        add_links("raylibdll", "raylib") 
        add_syslinks("gdi32", "winmm") 
    else
        --add_cxflags("-fsanitize=address");
        add_linkdirs("lib/linux") 
        add_links("libraylib.a")
        --add_syslinks("asan");
    end