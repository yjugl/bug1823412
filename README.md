# HookTests

Helper files for reproducing Firefox [bug 1823412](https://bugzilla.mozilla.org/show_bug.cgi?id=1823412).

## How to reproduce bug 1823412

- Install [the latest Microsoft Visual C++ Redistributable package for x64](https://aka.ms/vs/17/release/vc_redist.x64.exe).
- Download `HookTests.exe` and `HookLib.dll` from [this repository's release section](https://github.com/yjugl/bug1823412/releases/tag/v1.0). Keep them in the same folder.
- (Recommended) Check integrity of the files from a Powershell window. The hashes on your computer should match:

```
PS > Get-FileHash .\HookTests.exe

Algorithm       Hash                                                                   Path
---------       ----                                                                   ----
SHA256          5EBEDD581258A1C29F4883B8B443C2B4EF86F442C0D53954AA6E4A8409DAB14D       .\HookTests.exe

PS > Get-FileHash .\HookLib.dll

Algorithm       Hash                                                                   Path
---------       ----                                                                   ----
SHA256          CC4509C7D621B0F69584FF7FB082C9DC63C178133D03ED362C713DAF065D7C56       .\HookLib.dll
```

- Double click on `HookTests.exe`. SmartScreen prevents you from running the executable. Click `More info`, `Run anyway`.
- `HookTests.exe` launches and should show: `SUCCESS: The hook is installed`.
- Open Firefox and navigate to `about:third-party`. You should see `HookLib.dll` listed.
- In Firefox, click `Reload with system info`. A new button `Block this module` appears near `HookLib.dll`. Click it. Click `Restart Firefox now`.
- When Firefox restarts, it should be extremely slow. If you can, navigate to `about:processes`, it should show that the main process and the GPU process together use around 100% of CPU.
- Back in `HookTests.exe`, press ENTER, it should show: `SUCCESS: The hook is uninstalled`. Press ENTER again.
- Back in Firefox, you should now experience normal performance.
- Navigate to `about:third-party`. Click `Reload with system info`. Click the `Currently blocked` button near `HookLib.dll` to unblock the module.  Click `Restart Firefox now`.

## Building

- If you want to build your own versions of the executables, open the project in Visual Studio and build it with C++20 in x64 Release.
