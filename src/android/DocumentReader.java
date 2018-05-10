package cordova.plugin.documentreader;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.util.Base64;

import com.regula.documentreader.api.enums.DocReaderAction;
import com.regula.documentreader.api.enums.eGraphicFieldType;
import com.regula.documentreader.api.results.DocumentReaderJsonResultGroup;
import com.regula.documentreader.api.results.DocumentReaderResults;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;

/**
 * This class echoes a string called from JavaScript.
 */
public class DocumentReader extends CordovaPlugin {
    private CallbackContext callbackContext;
    private boolean status;


    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        this.callbackContext = callbackContext;
        if(action.equals("initReader")){
            Object license = args.get(0);
            this.initReader(license);
            return true;
        } else if(action.equals("scanDocument")){
            this.scanDocument();
            return true;
        }
        return false;
    }

    private void initReader(Object license){
        try{
            if(license!=null){
                byte[] licenseBytes = Base64.decode(license.toString(), Base64.DEFAULT);
                StringBuilder stringBuilder = new StringBuilder();
                com.regula.documentreader.api.DocumentReader.Instance().initializeReader(cordova.getActivity(), licenseBytes, new com.regula.documentreader.api.DocumentReader.DocumentReaderInitCompletion() {
                    @Override
                    public void onInitCompleted(boolean b, String s) {
                        status = b;
                        if(b){
                            callbackContext.success();
                        } else {
                            callbackContext.error("Initialization failed");
                        }
                    }
                });
            } else {
                callbackContext.error("License passed is null");
            }
        } catch(Exception ex){
            callbackContext.error(ex.getMessage());
        }
    }

    private void scanDocument(){
        if(status){
            if(cordova.hasPermission(Manifest.permission.CAMERA))                    {
                showScanner();
            }
            else{
                cordova.requestPermission(this,1,Manifest.permission.CAMERA);
            }
        }
    }

    @Override
    public void onRequestPermissionResult(int requestCode, String[] permissions,
                                          int[] grantResults) throws JSONException
    {
        for(int r:grantResults)
        {
            if(r == PackageManager.PERMISSION_DENIED)
            {
                this.callbackContext.error("Permission required!");
                return;
            }
        }
        switch(requestCode)
        {
            case 1:
                showScanner();
                break;
        }
    }

    private void showScanner() {
        com.regula.documentreader.api.DocumentReader.Instance().processParams.scenario = "MrzOrBarcode";

        com.regula.documentreader.api.DocumentReader.Instance().showScanner(new com.regula.documentreader.api.DocumentReader.DocumentReaderCompletion() {
            @Override
            public void onCompleted(int i, DocumentReaderResults documentReaderResults, String s) {
                switch (i){
                    case DocReaderAction.COMPLETE:
                        if(documentReaderResults!=null && documentReaderResults.jsonResult!=null) {
                            JSONObject resultObj = new JSONObject();
                            JSONArray jsonArray = new JSONArray();
                            int index = 0;
                            try {
                                for (DocumentReaderJsonResultGroup group : documentReaderResults.jsonResult.results) {
                                    jsonArray.put(index, new JSONObject(group.jsonResult));
                                    index++;
                                }
                                resultObj.put("jsonResult", jsonArray);

                                Bitmap bitmap = documentReaderResults.getGraphicFieldImageByType(eGraphicFieldType.GT_DOCUMENT_FRONT);
                                if(bitmap!=null) {
                                    ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                                    bitmap.compress(Bitmap.CompressFormat.JPEG, 80, byteArrayOutputStream);
                                    byte[] byteArray = byteArrayOutputStream.toByteArray();
                                    String encoded = Base64.encodeToString(byteArray, Base64.DEFAULT);
                                    resultObj.put("image", encoded);
                                }
                            } catch (Exception ex){
                                callbackContext.error(ex.getMessage());
                            }

                            callbackContext.success(resultObj);
                        }
                        break;
                    case DocReaderAction.CANCEL:
                        callbackContext.success("Cancelled by user");
                        break;
                    case DocReaderAction.ERROR:
                        callbackContext.error(s);
                        break;
                }
            }
        });
    }
}
