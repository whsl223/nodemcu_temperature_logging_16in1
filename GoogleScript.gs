var SS = SpreadsheetApp.openById('');
var str = "";

function doPost(e) {
  var parsedData;

  try { 
    parsedData = JSON.parse(e.postData.contents);
  } 
  catch(f){
    return ContentService.createTextOutput("Error in parsing request body: " + f.message);
  }
   
  if (parsedData !== undefined){
    var flag = parsedData.format;
    if (flag === undefined){
      flag = 0;
    }
    
    var sheet = SS.getSheetByName(parsedData.sheet_name); // sheet name to publish data to is specified in Arduino code
    var dataArr = parsedData.values.split(","); // creates an array of the values to publish 
    var [sensor01,sensor02,sensor03,sensor04,sensor05,sensor06,sensor07,sensor08,sensor09,sensor10,sensor11,sensor12,sensor13,sensor14,sensor15,sensor16, ...others] = dataArr


    switch (parsedData.command) {
      case "append_row":
         sheet.appendRow([
          Utilities.formatDate(new Date(), "Asia/Hong_Kong", "dd-MMM-yyyy"),
          Utilities.formatDate(new Date(), "Asia/Hong_Kong", "HH:mm:ss"),
          sensor01,sensor02,sensor03,sensor04,sensor05,sensor06,sensor07,sensor08,sensor09,sensor10,sensor11,sensor12,sensor13,sensor14,sensor15,sensor16
         ]);
         str = "Success"; // string to return back to Arduino serial console
         SpreadsheetApp.flush();
         break;     
    }
    return ContentService.createTextOutput(str);
  }
  
  else {
    return ContentService.createTextOutput("Error! Request body empty or in incorrect format.");
  }
}
