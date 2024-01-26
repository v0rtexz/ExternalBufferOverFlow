# Introduction
The SetWindowsHookEx function in Windows allows the installation of a hook routine into the hook chain, triggering specific events. Due to the absence of security checks, this function can be exploited to manipulate any application handling input through WndProc, without resorting to code injection techniques.

# Disclaimer
Caution: The following demonstration is intended for educational purposes only. Ethical and legal considerations must be observed when exploring software vulnerabilities. Unauthorized exploitation is strictly prohibited.

# Overview
This repository provides a simple example showcasing the potential misuse of SetWindowsHookEx. By setting the hook for a specified application (via its process ID), we demonstrate how an external payload can be executed without code injection. In the example code, a basic payload is executed, causing a buffer overflow that leads to a crash or freeze of the target application.
