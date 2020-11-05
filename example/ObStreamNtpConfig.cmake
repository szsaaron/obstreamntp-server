
set(ObStreamNtp_FOUND TRUE) # auto 
#set(ObStreamNtp_ROOT_DIR "/home/aaron/work/code/v4l/zmq/zmq-learn")
set(ObStreamNtp_ROOT_DIR "../")

find_path(ObStreamNtp_INCLUDE_DIR NAMES ObStreamNtp.h PATHS "${ObStreamNtp_ROOT_DIR}/include") 
#mark_as_advanced(ObStreamNtp_INCLUDE_DIR) # show entry in cmake-gui

find_library(ObStreamNtp_LIBRARY NAMES libObStreamNtp.so PATHS "${ObStreamNtp_ROOT_DIR}/lib") 
#mark_as_advanced(ObStreamNtp_LIBRARY) # show entry in cmake-gui

# use xxx_INCLUDE_DIRS and xxx_LIBRARIES in CMakeLists.txt
set(ObStreamNtp_INCLUDE_DIRS ${ObStreamNtp_INCLUDE_DIR})
set(ObStreamNtp_LIBRARIES ${ObStreamNtp_LIBRARY})

message("ObStreamNtpConfig.cmake" ${ObStreamNtp_ROOT_DIR})

