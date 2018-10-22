# Fuzz testing on JavaScriptCore and WebAssembly in WebKit

## 1. WebKit

### 1.1 About
WebKit is a browser engine used in Apple's Safari browser and other products.

WebKit is also the basis for the experimental browser included with the Amazon Kindle e-book reader, and for the default browser in Apple iOS, BlackBerry Browser in OS 6 and above, and Tizen mobile operating systems. WebKit's C++ application programming interface (API) provides a set of classes to display web content in windows, and implements browser features such as following links when clicked by the user, managing a back-forward list, and managing a history of pages recently visited.

WebKit's HTML and JavaScript code was originally a fork of the KHTML and KJS libraries from KDE, and has now been further developed by individuals from KDE, Apple, Google, Nokia, Bitstream, BlackBerry, Igalia, and others. macOS, Windows, Linux, and some other Unix-like operating systems are supported by the project. On April 3, 2013, Google announced that it had forked WebCore, a component of WebKit, to be used in future versions of Google Chrome and the Opera web browser, under the name Blink.

WebKit is available under a BSD-form license with the exception of the WebCore and JavaScriptCore components, which are available under the GNU Lesser General Public License. As of March 7, 2013, WebKit is a trademark of Apple, registered with the U.S. Patent and Trademark Office

### 1.2 JavaScriptCore

The JavaScriptCore Framework provides the ability to evaluate JavaScript programs from within Swift, Objective-C, and C-based apps. You can use also use JavaScriptCore to insert custom objects to the JavaScript environment.

### 1.3 WebAssembly

WebAssembly (abbreviated Wasm) is a binary instruction format for a stack-based virtual machine. Wasm is designed as a portable target for compilation of high-level languages like C/C++/Rust, enabling deployment on the web for client and server applications.

**Efficient and fast.**
The Wasm stack machine is designed to be encoded in a size- and load-time-efficient binary format. WebAssembly aims to execute at native speed by taking advantage of common hardware capabilities available on a wide range of platforms.

**Safe.**
WebAssembly describes a memory-safe, sandboxed execution environment that may even be implemented inside existing JavaScript virtual machines. When embedded in the web, WebAssembly will enforce the same-origin and permissions security policies of the browser.

**Open and debuggable.**
WebAssembly is designed to be pretty-printed in a textual format for debugging, testing, experimenting, optimizing, learning, teaching, and writing programs by hand. The textual format will be used when viewing the source of Wasm modules on the web.

**Part of the open web platform.**
WebAssembly is designed to maintain the versionless, feature-tested, and backwards-compatible nature of the web. WebAssembly modules will be able to call into and out of the JavaScript context and access browser functionality through the same Web APIs accessible from JavaScript. WebAssembly also supports non-web embeddings.

## 2. Deploy And Setup

### 2.1 Building WebKit

Building macOS Port
Install Xcode and its command line tools if you haven't done so already:

Install Xcode Get Xcode from https://developer.apple.com/downloads. To build WebKit for OS X, Xcode 5.1.1 or later is required. To build WebKit for iOS Simulator, Xcode 7 or later is required.
1. Install the Xcode Command Line Tools In Terminal, run the command: xcode-select --install
2. Run the following command to build a debug build with debugging symbols and assertions:

    Tools/Scripts/build-webkit --debug

For performance testing, and other purposes, use --release instead.

Using Xcode
You can open WebKit.xcworkspace to build and debug WebKit within Xcode.

If you don't use a custom build location in Xcode preferences, you have to update the workspace settings to use WebKitBuild directory. In menu bar, choose File > Workspace Settings, then click the Advanced button, select "Custom", "Relative to Workspace", and enter WebKitBuild for both Products and Intermediates.

Building iOS Port
The first time after you install a new Xcode, you will need to run the following command to enable Xcode to build command line tools for iOS Simulator:

    sudo Tools/Scripts/configure-xcode-for-ios-development

Without this step, you will see the error message: "target specifies product type ‘com.apple.product-type.tool’, but there’s no such product type for the ‘iphonesimulator’ platform." when building target JSCLLIntOffsetsExtractor of project JavaScriptCore.

Run the following command to build a debug build with debugging symbols and assertions for iOS:

    Tools/Scripts/build-webkit --debug --ios-simulator.

##### Building the GTK+ Port
##### For production builds:

    cmake -DPORT=GTK -DCMAKE_BUILD_TYPE=RelWithDebInfo -GNinja
    ninja
    sudo ninja install

##### For development builds:

    Tools/gtk/install-dependencies
    Tools/Scripts/update-webkitgtk-libs
    Tools/Scripts/build-webkit --gtk --debug

For more information on building WebKitGTK+, see the wiki page.

#### Building the WPE Port
For production builds:

    cmake -DPORT=WPE -DCMAKE_BUILD_TYPE=RelWithDebInfo -GNinja
    ninja
    sudo ninja install

#### For development builds:

Tools/wpe/install-dependencies
Tools/Scripts/update-webkitwpe-libs
Tools/Scripts/build-webkit --wpe --debug
Building Windows Port
For building WebKit on Windows, see the wiki page.

#### Running WebKit
With Safari and Other macOS Applications
Run the following command to launch Safari with your local build of WebKit:

    Tools/Scripts/run-safari --debug

The run-safari script sets the DYLD_FRAMEWORK_PATH environment variable to point to your build products, and then launches /Applications/Safari.app. DYLD_FRAMEWORK_PATH tells the system loader to prefer your build products over the frameworks installed in /System/Library/Frameworks.

To run other applications with your local build of WebKit, run the following command:

    Tools/Scripts/run-webkit-app <application-path>

#### iOS Simulator
Run the following command to launch iOS simulator with your local build of WebKit:

    run-safari --debug --ios-simulator

In both cases, if you have built release builds instead, use --release instead of --debug.

#### Linux Ports
If you have a development build, you can use the run-minibrowser script, e.g.:

    run-minibrowser --debug --wpe

Pass one of --gtk, --jsc-only, or --wpe to indicate the port to use.


### 2.2 Build Fuzzer

One way is to change the JSC file. Another way is to change WASM file.
You really need a driver to start the testing on WASM, see Fuzzing folder.

    make
    cd llvm_mode && make
    cd .. && make && make install
    cd Fuzzing

    //driver in the Fuzzig folder
    ...

## 3. Common vulnerabilities

### 3.1 Memory Leak in Webkit

![alt](./docs/Memleak.png)

### 3.2 MInvalid Address Read in Webkit

![alt](./docs/Address.png)

