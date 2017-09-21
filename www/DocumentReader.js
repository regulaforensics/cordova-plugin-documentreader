module.exports = {
    scanDocument: function (license, successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "DocumentReader", "scanDocument", [license]);
    }
};