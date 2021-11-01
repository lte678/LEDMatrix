//
// Created by leon on 4/23/19.
//

#include "ServiceUtils.h"

/// Checks if the matrix service is running on the system
bool serviceRunning() {
    FILE *shell;
    char state[16];

    shell = popen("systemctl show -p SubState --value matrix", "r");
    fgets(state, 16, shell);
    fclose(shell);

    return strcmp("running", state) == 0;
}