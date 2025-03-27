#include <sys/mman.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#include <fstream>

intptr_t slide = _dyld_get_image_vmaddr_slide(1);

typedef int (*lua_CFunction)(long);

typedef long (*lua_newuserdatatagged_t)(long, long, int);
lua_newuserdatatagged_t lua_newuserdatatagged = (lua_newuserdatatagged_t)(0x1024953b4 + slide);

typedef long (*lua_topointer_t)(long, int);
lua_topointer_t lua_topointer = (lua_topointer_t)(0x102493bd0 + slide);

typedef void (*lua_pushcclosurek_t)(long, lua_CFunction, const char*, int, int);
lua_pushcclosurek_t lua_pushcclosurek = (lua_pushcclosurek_t)(0x102493ecc + slide);

typedef void (*lua_replace_t)(long, int);
lua_replace_t lua_replace = (lua_replace_t)(0x102492d30 + slide);

typedef int (*lua_rawseti_t)(long, int, int);
lua_rawseti_t lua_rawseti = (lua_rawseti_t)(0x102494b30 + slide);

typedef void (*lua_call_t)(long, int, int);
lua_call_t lua_call = (lua_call_t)(0x102494e00 + slide);

typedef int (*lua_setmetatable_t)(long, int);
lua_setmetatable_t lua_setmetatable = (lua_setmetatable_t)(0x102494c10 + slide);

typedef int (*lua_getfield_t)(long, int, const char*);
lua_getfield_t lua_getfield = (lua_getfield_t)(0x102494144 + slide);

typedef int (*lua_rawgeti_t)(long, int, int);
lua_rawgeti_t lua_rawgeti = (lua_rawgeti_t)(0x1024943a4 + slide);

//typedef int (*lua_rawget_t)(long, int);
//lua_rawget_t lua_rawget = (lua_rawget_t)(0x1024942fc + slide);

typedef void (*lua_createtable_t)(long, int, int);
lua_createtable_t lua_createtable = (lua_createtable_t)(0x10249445c + slide);

typedef void (*lua_setfield_t)(long, int, const char*);
lua_setfield_t lua_setfield = (lua_setfield_t)(0x10249488c + slide);

typedef void (*lua_pushvalue_t)(long, int);
lua_pushvalue_t lua_pushvalue = (lua_pushvalue_t)(0x102492e60 + slide);

typedef int (*lua_getmetatable_t)(long, int);
lua_getmetatable_t lua_getmetatable = (lua_getmetatable_t)(0x10249462c + slide);

typedef void (*lua_setreadonly_t)(long, int, bool);
lua_setreadonly_t lua_setreadonly = (lua_setreadonly_t)(0x1024944f0 + slide);

typedef int (*lua_tointegerx_t)(long, int, int*);
lua_tointegerx_t lua_tointegerx = (lua_tointegerx_t)(0x102493304 + slide);

typedef bool (*lua_toboolean_t)(long, int);
lua_toboolean_t lua_toboolean = (lua_toboolean_t)(0x102493444 + slide);

typedef const char* (*lua_tolstring_t)(long, int, size_t);
lua_tolstring_t lua_tolstring = (lua_tolstring_t)(0x1024934c0 + slide);

typedef void (*lua_xmove_t)(long, long, int);
lua_xmove_t lua_xmove = (lua_xmove_t)(0x102492978 + slide);

typedef long (*lua_newthread_t)(long);
lua_newthread_t lua_newthread = (lua_newthread_t)(0x102492aac + slide);

typedef long (*lua_mainthread_t)(long);
lua_mainthread_t lua_mainthread = (lua_mainthread_t)(0x102492b54 + slide);

typedef int (*luau_load_t)(long, const char*, const char*, size_t, int);
luau_load_t luau_load = (luau_load_t)(0x1024b6e7c + slide);

typedef int (*lua_resume_t)(long, long, int);
lua_resume_t lua_resume = (lua_resume_t)(0x10249e940 + slide);

typedef long (*get_identity_pointer_t)();
get_identity_pointer_t get_identity_pointer = (get_identity_pointer_t)(0x10306615c + slide);

typedef int (*lua_gettop_t)(long);
lua_gettop_t lua_gettop = (lua_gettop_t)(0x102492b94 + slide);

typedef long (*sub1_t)(long);
sub1_t sub1 = (sub1_t)(0x100cf9c20 + slide);

typedef long (*sub2_t)(long);
sub2_t sub2 = (sub2_t)(0x102494eb8 + slide);

typedef long (*sub3_t)(long, long);
sub3_t sub3 = (sub3_t)(0x100cfb574 + slide);

typedef void (*sub4_t)(long, int, long);
sub4_t sub4 = (sub4_t)(0x100cf8810 + slide);

std::string challenge = std::string("=challenge");
std::string script_bytecode;
long roblox_state = 0;

struct Event {
    long pointer;
    int function;
};

void lua_pushraw(long lua_state, long value, int tt) {
    long* top = *(long**)(lua_state + 0x20);
    *top = value;
    *(int*)((long)top + 0xc) = tt;
    *(long*)(lua_state + 0x20) = *(long*)(lua_state + 0x20) + 0x10;
}

void lua_setidentity(long lua_state, int identity) {
    long permission = sub2(lua_state);
    long identity_pointer = get_identity_pointer();
    
    *(int*)(permission+0x30) = identity;
    *(long*)(permission+0x48) = 0xffffffffffffffff;
    
    *(int*)identity_pointer = identity;
    *(bool*)(identity_pointer+0x20) = true;
}

int blank(long _) {
    return 0;
}

int disable(long lua_state) {
    Event* event = (Event*)lua_topointer(lua_state, 1);
    
    if (event != 0) {
        long pointer_1 = *(long*)(event->pointer + 0x30);
        
        if (pointer_1 != 0) {
            long pointer_2 = *(long*)(pointer_1 + 0x70);
            
            if (pointer_2 != 0) {
                *(int*)(pointer_2 + 0x14) = 0;
            }
        }
    } else {
        printf("\n\nThe Event was transmitted incorrectly.\n\n");
    }
    return 0;
}

int enable(long lua_state) {
    Event* event = (Event*)lua_topointer(lua_state, 1);
    
    if (event != 0) {
        long pointer_1 = *(long*)(event->pointer + 0x30);
        
        if (pointer_1 != 0) {
            long pointer_2 = *(long*)(pointer_1 + 0x70);
            
            if (pointer_2 != 0) {
                *(int*)(pointer_2 + 0x14) = event->function;
            }
        }
    } else {
        printf("\n\nThe Event was transmitted incorrectly.\n\n");
    }
    return 0;
}

int fire(long lua_state) {
    lua_getfield(lua_state, 1, "Function");
    lua_replace(lua_state, 1);
    lua_call(lua_state, lua_gettop(lua_state)-1, 0);
    return 0;
}

int eventindex(long lua_state) {
    Event* event = (Event*)lua_topointer(lua_state, 1);
    std::string key = lua_tolstring(lua_state, 2, 0);
    
    if (key == "Function") {
        lua_rawgeti(lua_state, -10000, event->function);
        
        if (*(int*)(*(long*)(lua_state + 0x20) - 0x4) != 8) {
            lua_rawgeti(lua_state, -10000, 0);
        }
    } else if (key == "State") {
        long status = *(long*)(event->pointer + 0x20);
        
        lua_pushraw(lua_state, status != 0 ? *(int*)status : 0, 1);
    } else if (key == "Disable") {
        lua_pushcclosurek(lua_state, disable, 0, 0, 0);
    } else if (key == "Enable") {
        lua_pushcclosurek(lua_state, enable, 0, 0, 0);
    } else if (key == "Fire") {
        lua_pushcclosurek(lua_state, fire, 0, 0, 0);
    } else {
        lua_pushraw(lua_state, 0, 0);
    };
    
    return 1;
};

int getrawmetatable(long lua_state) {
    return lua_getmetatable(lua_state, 1);
}

int setreadonly(long lua_state) {
    lua_setreadonly(lua_state, 1, lua_toboolean(lua_state, 2));
    return 0;
}

int set_thread_identity(long lua_state) {
    lua_setidentity(lua_state, lua_tointegerx(lua_state, 1, 0));
    return 0;
}

int writeconsole(long lua_state) {
    printf("%s\n", lua_tolstring(lua_state, 1, 0));
    return 0;
}

int getreg(long lua_state) {
    lua_pushvalue(lua_state, -10000);
    return 1;
}

int getrenv(long lua_state) {
    if (roblox_state != 0) {
        lua_pushvalue(roblox_state, -10002);
        lua_xmove(roblox_state, lua_state, 1);
        return 1;
    }
    printf("\n\nRoblox State is invalid.\n\n");
    return 0;
}

int getupvalues(long lua_state) {
    long func = lua_topointer(lua_state, 1);

    if (func && *(uint8_t*)func == 8) {
        uint8_t count = *(uint8_t*)(func + 4);
        
        lua_createtable(lua_state, 0, 0);
        
        long offset = *(bool*)(func + 3) ? func + 48 : func + 32;
        
        for (int i = 0; i < count; i++) {
            long upvalue = offset + 16 * i;
            long value = *(long*)upvalue;
            int tt = *(int*)(upvalue + 12);
            
            if (tt == 12) {
                long v = *(long*)(value + 8);
                lua_pushraw(lua_state, *(long*)v, *(int*)(v + 12));
            } else {
                lua_pushraw(lua_state, value, tt);
            }
            
            lua_rawseti(lua_state, -2, i+1);
        }
        
        return 1;
    } else {
        printf("\n\nThe function was passed incorrectly.\n\n");
    }
    
    return 0;
}

int setupvalue(long lua_state) {
    long func = lua_topointer(lua_state, 1);
    
    if (func && *(uint8_t*)func == 8) {
        int idx = lua_tointegerx(lua_state, 2, 0)-1;
        
        if (idx > -1 && idx < *(uint8_t*)(func + 4)) {
            long nupvalue = (*(bool*)(func + 3) ? func + 48 : func + 32) + 16 * idx;
            
            long old_v = *(int*)(nupvalue + 12) == 12 ? *(long*)(*(long*)nupvalue + 8) : nupvalue;
            long new_v = *(long*)(lua_state + 0x30) + 0x20;
            
            *(long*)old_v = *(long*)new_v;
            *(int*)(old_v + 12) = *(int*)(new_v + 12);
        } else {
            printf("\n\nIncorrect index.\n\n");
        }
    } else {
        printf("\n\nThe function was passed incorrectly.\n\n");
    }
    
    return 0;
}

int getconnections(long lua_state) {
    lua_getfield(lua_state, 1, "Connect");
    lua_pushvalue(lua_state, 1);
    lua_rawgeti(lua_state, -10000, 0);
    lua_call(lua_state, 2, 1);
    
    long next = *(long*)(*(long*)lua_topointer(lua_state, -1) + 0x10);
    lua_createtable(lua_state, 0, 0);
    int index = 1;
    
    while (next != 0) {
        Event* data = (Event*)lua_newuserdatatagged(lua_state, 12, 0);
        struct Event e;
        e.pointer = next;
        
        long pointer_1 = *(long*)(next + 0x30);
        
        if (pointer_1 != 0) {
            long pointer_2 = *(long*)(pointer_1 + 0x70);
            
            if (pointer_2 != 0) {
                e.function = *(int*)(pointer_2 + 0x14);
            }
        }
        
        *data = e;
        lua_createtable(lua_state, 0, 0);
        lua_pushcclosurek(lua_state, eventindex, 0, 0, 0);
        lua_setfield(lua_state, -2, "__index");
        lua_setmetatable(lua_state, -2);
        lua_rawseti(lua_state, -2, index);
    
        next = *(long*)(next + 0x10);
        
        index++;
    }
    
    lua_getfield(lua_state, -2, "Disconnect");
    lua_pushvalue(lua_state, -3);
    lua_call(lua_state, 1, 0);
    return 1;
}

int fake_load(long lua_state, const char* chunkname, const char* data, long size, int env) {
    printf("\n\n%s\n\n", chunkname);
    
    std::string input;
    for (int i = 0; i < size; i++) {
        input.append(std::to_string(*(uint8_t*)((long)data+i))+=';');
    }
    
    printf("\n\n%s\n\n", input.data());
    
    if (challenge == chunkname) {
        roblox_state = 0;
        long thread = lua_newthread(lua_mainthread(lua_state));
        
        lua_createtable(thread, 0, 0);
        lua_createtable(thread, 0, 0);
        
        lua_pushvalue(thread, -10002);
        lua_setfield(thread, -2, "__index");
        lua_setreadonly(thread, -1, true);
        
        lua_setmetatable(thread, -2);
        
        lua_replace(thread, -10002);
        
        lua_pushcclosurek(thread, getrawmetatable, "getrawmetatable", 0, 0);
        lua_setfield(thread, -10002, "getrawmetatable");
        
        lua_pushcclosurek(thread, setreadonly, "setreadonly", 0, 0);
        lua_setfield(thread, -10002, "setreadonly");
        
        lua_pushcclosurek(thread, set_thread_identity, "set_thread_identity", 0, 0);
        lua_setfield(thread, -10002, "set_thread_identity");
        
        lua_pushcclosurek(thread, writeconsole, "writeconsole", 0, 0);
        lua_setfield(thread, -10002, "writeconsole");
        
        lua_pushcclosurek(thread, getreg, "getreg", 0, 0);
        lua_setfield(thread, -10002, "getreg");
        
        lua_pushcclosurek(thread, getrenv, "getrenv", 0, 0);
        lua_setfield(thread, -10002, "getrenv");
        
        lua_pushcclosurek(thread, getupvalues, "getupvalues", 0, 0);
        lua_setfield(thread, -10002, "getupvalues");

        lua_pushcclosurek(thread, setupvalue, "setupvalue", 0, 0);
        lua_setfield(thread, -10002, "setupvalue");
        
        lua_pushcclosurek(thread, getconnections, "getconnections", 0, 0);
        lua_setfield(thread, -10002, "getconnections");
        
        lua_pushcclosurek(thread, blank, "blank", 0, 0);
        lua_rawseti(thread, -10000, 0);

        lua_setidentity(thread, 7);
        
        if (luau_load(thread, "=Povidlo", script_bytecode.c_str(), script_bytecode.size(), 0) == 0) {
            sub4(thread, -1, sub3(sub1(thread), 0xffffffffffffffff));
            if (lua_resume(thread, 0, 0) == 2) {
                printf("\n\nThe injector startup error: %s\n\n", lua_tolstring(thread, -1, 0));
            }
        } else {
            printf("\n\nError loading the byte code.\n\n");
        }
    } else if (roblox_state == 0) {
        roblox_state = lua_newthread(lua_state);
    }
    
    return luau_load(lua_state, chunkname, data, size, env);
}

void* init(void * args) {
    printf("\n\nPovidlo ALPHA v1.1\n\n");
    
    std::ifstream dataFile(".data.txt");
    std::string chr;
    
    while (getline(dataFile, chr, ';')) {
        script_bytecode += (char)std::stoi(chr.c_str());
    }
    
    long addr = 0x100cc61f8 + slide;
    int bytes = (0x25 << 26) + (int)(((long)&fake_load - addr) / 4);
    
    int page_size = getpagesize();
    void* page_start = (void*)(addr & ~(page_size - 1));
    
    void* chunk = malloc(page_size);
    memcpy(chunk, page_start, page_size);
    mmap(page_start, page_size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    memcpy(page_start, chunk, page_size);
    free(chunk);
    
    memcpy((void*)addr, &bytes, 4);
    
    mprotect(page_start, page_size, PROT_EXEC | PROT_READ);
    
    return 0;
}

__attribute__((constructor))
void runner(int argc, const char * argv[]) {
    if (argc == 1) {
        pthread_t thread;
        pthread_create(&thread, NULL, &init, NULL);
    }
}
 
