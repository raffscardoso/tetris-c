var statusElement = document.getElementById('status');
var canvasElement = document.getElementById('canvas');

var Module = {
  print: function(text) { console.log(text); },
  printErr: function(text) { console.error(text); },
  canvas: canvasElement,
  setStatus: function(text) {
    if (!text) {
      statusElement.style.display = 'none';
    } else {
      statusElement.innerHTML = text;
    }
  },
  monitorRunDependencies: function(left) {
    this.setStatus(left ? 'Preparing... (' + left + ')' : '');
  }
};

Module.setStatus('Downloading...');

window.onerror = function() {
  Module.setStatus('Exception thrown, see JavaScript console');
};
