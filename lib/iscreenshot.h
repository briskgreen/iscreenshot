/*iscreenshot库头文件
 * 该头文件包含了所有iscreenshot所需要的头文件
 * 作者:炕头哥
 * Copyright © 2013-07 By 炕头哥
 * 许可协议:libiscreenshot遵循LGPL许可协议发布
 * 联系作者:briskgreen@163.com
 * 对于LGPL许可土方的具体内容可参考下面的连接
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef _ISCREENSHOT_H
#define _ISCREENSHOT_H

#include "iscreenshot_get_root_window.h"
#include "iscreenshot_get_active_window.h"
#include "iscreenshot_get_rectangle_window.h"
#include "iscreenshot_save.h"
#include <errno.h>

void error_quit(const char *msg);

#endif
