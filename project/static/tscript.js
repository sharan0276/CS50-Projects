var t;
var x = -9999;

function resetTimer() {
    clearInterval(x);
    document.getElementById("hour").innerHTML = '';
    document.getElementById("minute").innerHTML = '' ;
    document.getElementById("second").innerHTML = '';
    document.getElementById("expire").innerHTML = '';
}

function countdown() {
  resetTimer();
  var days = 0;
  var time = document.querySelector("#time").value;
  var t = time.split(':');
  var hours = parseInt(t[0]);
  var minutes = parseInt(t[1]);
  var seconds = parseInt(t[2]);

  if ( (hours == 0 && minutes == 0 && seconds == 0) || time === '') {
    alert("Please provide duration. \n Like 1:30:00, 3:50:15");
    return ;
  }

  if (isNaN(hours) || isNaN(minutes) || isNaN(seconds) || seconds > 59 || minutes > 59) {
    alert("Please provide a valid duration.");
    return ;
  }

  var h = 0, m = 0, s = 0;

  if (hours != 0) {
    h = 1;
  }

  if (minutes != 0) {
    m = 1;
  }

  if (seconds != 0) {
    s = 1;
  }


  x = setInterval(function() {

    document.getElementById("hour").innerHTML = hours;
    document.getElementById("minute").innerHTML = minutes;
    document.getElementById("second").innerHTML = seconds;

    if (h != 0) {
      if (hours == 0 && minutes == 0 && seconds == 0) {
        clearInterval(x);
        document.getElementById("hour").innerHTML = '0';
        document.getElementById("minute").innerHTML = '0' ;
        document.getElementById("second").innerHTML = '0';
      }
      if (seconds == 0) {
        if (minutes == 0) {
          minutes = 60;
        }
        minutes = minutes - 1;
        seconds = 60;
      }
      seconds = seconds - 1;

      if (minutes == 0) {
        minutes = 59;
        hours = hours - 1;
      }
    }

    if (h == 0 && m == 0) {
      hours = 0;
      minutes = 0;

      seconds = seconds - 1;

      if (hours == 0 && minutes == 0 && seconds == 0) {
        clearInterval(x);
        document.getElementById("hour").innerHTML = '0';
        document.getElementById("minute").innerHTML = '0' ;
        document.getElementById("second").innerHTML = '0';
      }
    }

    if (h == 0 ) {
      hours = 0;

      if (m != 0) {
        if (seconds == 0) {
          minutes = minutes - 1;
          seconds = 60;
        }
        seconds = seconds - 1;
      }

      if (hours == 0 && minutes == 0 && seconds == 0) {
        clearInterval(x);
        document.getElementById("hour").innerHTML = '0';
        document.getElementById("minute").innerHTML = '0' ;
        document.getElementById("second").innerHTML = '0';
        document.getElementById("expire").innerHTML = 'Timer Expired';
      }
    }

  }, 1000);
}