# Picobook-X
Launch Picotron by Lexaloffle at the correct screen resolution on the Chuwi Minibook X, then switch back to the original resolution upon exit.


**Introduction**

[Picotron](picotron.net) is the last fantasy Fantasy Workstation created by Lexaloffle, running at a native resolution of 480x270. The Chuwi Minibook X is a compact 10.51-inch laptop featuring a full-size keyboard and a native resolution of 1440x900. Picobook-X aims to facilitate launching Picotron at the optimal resolution on the Chuwi Minibook X, then reverting to the original resolution upon exit.


**Compilation**

Simply use [w64devkit by skeeto](https://github.com/skeeto/w64devkit): ```g++ -O3 -std=c++17 -o picobookx.exe picobookx.cpp -lstdc++fs```


**How to**

Put picobookx.exe in your picotron folder, next to picotron.exe, and launch it!
