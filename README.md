# ExternalBufferOverFlow
 
SetWindowsHookEx installs a hook routine into the hook chain, and it is invoked whenever specific events are triggered.
Since Windows has no security regarding this function, we can abuse it to let any application which handles input through WndProc call our payload function.

This happens without any code injection.

In the example code We set the hook for the given application (through its process id) and execute a payload which causes a buffer overflow leading to a crash or freeze of the target application.
