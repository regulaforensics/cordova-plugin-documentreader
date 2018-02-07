# cordova-plugin-documentreader
Cordova plugin for reading and validation of identification documents. Using [Regula Document Reader](https://github.com/regulaforensics/DocumentReader-iOS) with core DocumentReaderMRZBarcode.framework inside for iOS version.

## Install
Install plugn:
```
cordova plugin add cordova-plugin-documentreader --variable CAMERA_USAGE_DESCRIPTION="To take photo" --save
```

## Usage
You can get trial license for demo application at [licensing.regulaforensics.com](https://licensing.regulaforensics.com) (`regula.license` file).

InitializeReader:
```
DocumentReader.initReader(
    license,
    function (result) {
        // result will contain array of json results.
    },
    function () {
        alert("Error calling DocumentReader Plugin");
    }
);
```

ScanDocument:
```
DocumentReader.scanDocument(
    function (result) {
        // result will contain array of json results.
    },
    function () {
        alert("Error calling DocumentReader Plugin");
    }
);
```

## How to build demo application
1. Open terminal inside empty folder and run ``` cordova create testdocumentreader <YOUR_APPLICATION_ID> DocumentReaderTest ```
2. Run  ```cd testdocumentreader```
3. Add plugin: ``` cordova plugin add cordova-plugin-documentreader --variable CAMERA_USAGE_DESCRIPTION="To take photo" --save ```
3. Add cordova-plugin-file for get license file: ``` cordova plugin add cordova-plugin-file --save```
4. Get trial license for demo application at [licensing.regulaforensics.com](https://licensing.regulaforensics.com) (`regula.license` file). When you will create license use  ```<YOUR_APPLICATION_ID>``` like bundle ID (see the first paragraph).
5. Put license to `www/regula.license`.
6. Put this code inside onDeviceReady method file `index.js` (path: `www/js/index.js`) for calling DocumentReader plugin:
```
onDeviceReady: function() {
    this.receivedEvent('deviceready');

    window.resolveLocalFileSystemURL(
        cordova.file.applicationDirectory + "www/regula.license",
        function (fileEntry) {
            fileEntry.file(function(file) {
                var reader = new FileReader();
                reader.onloadend = function(e) {
                    DocumentReader.initReader(
                        this.result,
                        function (message) {
                            DocumentReader.scanDocument(
                                function (message) {
                                    alert(message);
                                },
                                function (error) {
                                    alert(error);
                                }
                            );
                        },
                        function (error) {
                            alert(error);
                        }
                    );
                }
                reader.readAsArrayBuffer(file);
            });
        }, function(e) {
            console.log("FileSystem Error");
            console.dir(e);
        });
},
```
7. Run ```cordova platform add ios```
8. Run iOS project.
