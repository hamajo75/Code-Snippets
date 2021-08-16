# nested functions
def scope_test():
    def do_local():
        print("do_local")

    do_local()
store_fun = scope_test

store_fun()