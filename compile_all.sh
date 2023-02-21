pgcc -Minfo=accel -fast -acc=gpu double_sin.c -o double_sin_g
pgcc -Minfo=accel -fast -acc=host double_sin.c -o double_sin_h
pgcc -Minfo=accel -fast -acc=multicore double_sin.c -o double_sin_mc
pgcc -Minfo=accel -fast -acc=gpu float_sin.c -o float_sin_g
pgcc -Minfo=accel -fast -acc=host float_sin.c -o float_sin_h
pgcc -Minfo=accel -fast -acc=multicore float_sin.c -o float_sin_mc