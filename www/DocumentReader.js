var documentReader = {};

documentReader.scanDocument = function (license, successCallback, errorCallback) {
    cordova.exec(successCallback, errorCallback, "DocumentReader", "scanDocument", [license]);
}

module.exports = documentReader;