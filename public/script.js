
function ngeprint() {
  window.print();
}

    var firebaseConfig = {
    databaseURL: "https://megaboth007.firebaseio.com/"};
    firebase.initializeApp(firebaseConfig);

/*
function renderTable(){
    var order =firebase.database().ref("nomor/").orderByKey();
    order.on("value", function (snapshot) {
    snapshot.forEach(function (childSnapshot) {
    var key = childSnapshot.key;
    var childData = childSnapshot.val(); 
    var orderValue =  childSnapshot.val();
      document.getElementById("table").innerHTML+=
      ` <tr><td id="btnBuy">${orderValue}</td></tr> `;                                                             
            });
    });
}
*/
function renderTable1(){
    var order =firebase.database().ref("waktu").orderByKey();
  //  var order =firebase.database().ref("nama").orderByKey();

    order.on("value", function (snapshot) {
            snapshot.forEach(function (childSnapshot) {
    var key = childSnapshot.key;
    var childData = childSnapshot.val(); 
    var orderValue =  childSnapshot.val();
      document.getElementById("table1").innerHTML+= ` 
      <tr>
      <td id="btnBuy">${orderValue}</td>
        </tr> 
        `;                                                             
            });
    });
}



function myFunction() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[0];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}

   