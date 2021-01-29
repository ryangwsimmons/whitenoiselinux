from fbs_runtime.application_context.PyQt5 import ApplicationContext
from WNLMainWindow import WNLMainWindow

import sys

if __name__ == '__main__':
    appctxt = ApplicationContext()       # 1. Instantiate ApplicationContext
    window = WNLMainWindow(appctxt)
    window.show()
    exit_code = appctxt.app.exec_()      # 2. Invoke appctxt.app.exec_()
    sys.exit(exit_code)