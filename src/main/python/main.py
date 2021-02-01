# Disable pygame welcome message, needs to run here so that it's set before the module is imported
from os import environ
environ["PYGAME_HIDE_SUPPORT_PROMPT"] = "1"

from fbs_runtime.application_context import cached_property
from fbs_runtime.application_context.PyQt5 import ApplicationContext
from WNLMainWindow import WNLMainWindow
import sys

# Overriding the app method so that QApplication is instantiated with the argument vector passed in
# This makes it so that the name of the app is shown next the activities menu in GNOME, as well as in other locations
class WNLAppContext(ApplicationContext):
    @cached_property
    def app(self):
        result = self._qt_binding.QApplication(sys.argv)
        result.setApplicationName("White Noise Linux")
        result.setApplicationVersion(self.build_settings['version'])
        return result

if __name__ == '__main__':
    appctxt = WNLAppContext()            # 1. Instantiate ApplicationContext
    window = WNLMainWindow(appctxt)
    window.show()
    exit_code = appctxt.app.exec_()      # 2. Invoke appctxt.app.exec_()
    sys.exit(exit_code)