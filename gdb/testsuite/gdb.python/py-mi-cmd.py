import gdb

class BadKey:
    def __repr__(self):
        return "Bad Kay"

class ReallyBadKey:
    def __repr__(self):
        return BadKey()


class pycmd1(gdb.MICommand):
    def invoke(self, argv):
        if argv[0] == 'int':
            return 42
        elif argv[0] == 'str':
            return "Hello world!"
        elif argv[0] == 'ary':
            return [ 'Hello', 42 ]
        elif argv[0] == "dct":
            return { 'hello' : 'world', 'times' : 42}
        elif argv[0] == "bk1":
            return { BadKey() : 'world' }
        elif argv[0] == "bk2":
            return { 1 : 'world' }
        elif argv[0] == "bk3":
            return { ReallyBadKey() : 'world' }
        elif argv[0] == 'tpl':
            return ( 42 , 'Hello' )
        elif argv[0] == 'itr':
            return iter([1,2,3])
        elif argv[0] == 'nn1':
            return None
        elif argv[0] == 'nn2':
            return [ None ]
        elif argv[0] == 'red':
            pycmd2('-pycmd')
            return None
        elif argv[0] == 'exp':
            raise gdb.GdbError()
        else:
            raise gdb.GdbError("Invalid parameter: %s" % argv[0])


class pycmd2(gdb.MICommand):
    def invoke(self, argv):
        if argv[0] == 'str':
            return "Ciao!"
        elif argv[0] == 'red':
            pycmd1('-pycmd')
            raise gdb.GdbError("Command redefined but we failing anyway")
        else:
            raise gdb.GdbError("Invalid parameter: %s" % argv[0])

