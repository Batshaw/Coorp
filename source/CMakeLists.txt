add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build test2
add_executable(test2
test2.cpp)
target_link_libraries(test2
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )


# Build test_r
add_executable(test_r
test_r.cpp)
target_link_libraries(test_r
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )
