target remote localhost:3333
monitor arm semihosting enable
load
monitor reset halt 
monitor resume