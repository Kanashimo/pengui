project('pengui', 'cpp', default_options: ['cpp_std=c++20'])

add_project_arguments(
  '-DGLFW_INCLUDE_NONE',
  language: 'cpp'
)

glib = dependency('glib-2.0')
gio = dependency('gio-2.0')
libportal = dependency('libportal')
gdk_pixbuf = dependency('gdk-pixbuf-2.0')
gtk = dependency('gtk4')
glfw = dependency('glfw3')
imgui = dependency('imgui', version: '>=1.92.6')
glbinding = dependency('glbinding')

sources = files(
    'src/main.cpp',
    'src/Application.cpp',
    'src/ScreenCapture/ScreenCapture.cpp',
    'src/ScreenCapture/ScreenCaptureError.cpp',
    'src/ShaderLoader/ShaderLoader.cpp',
    'src/UI/BackgroundTexture.cpp',
    'src/UI/Crop.cpp',
    'src/UI/Toolbar.cpp',
    'src/UI/Pipette.cpp',
    'src/UI/Ruler.cpp'
)

shaders = files(
  'src/Shaders/Glow/vert.glsl',
  'src/Shaders/Glow/frag.glsl'
)

fs = import('fs')

bash = find_program('bash', required: true)

find_program('xxd', required: true)
find_program('sed', required: true)
find_program('cp', required: true)
find_program('mkdir', required: true)

foreach f : shaders

  custom_target(
    'shader_' + fs.name(fs.parent(f)) + '_' + fs.name(f),
    input: f,
    output: fs.name(fs.parent(f)) + '.' + fs.name(f) + '.generated',
    command: [
      bash,
      files('scripts/copy_shader.sh'),
      meson.project_build_root(),
      fs.parent(f),
      fs.name(f),
    ],
    build_by_default: true,
  )

endforeach

## VERY VERY VERY VERY TEMPORARY SOLUTION, I DON'T HAVE TIME FOR THIS
roboto_regular = custom_target(
  'build_fonts1',
  input: 'src/Fonts/Roboto-Regular.ttf',
  output: 'Roboto_Regular.h',
  command: [bash, files('scripts/build_font.sh'), '@INPUT@', '@OUTPUT@'],
)

roboto_bold = custom_target(
  'build_fonts2',
  input: 'src/Fonts/Roboto-Bold.ttf',
  output: 'Roboto_Bold.h',
  command: [bash, files('scripts/build_font.sh'), '@INPUT@', '@OUTPUT@'],
)

roboto_light = custom_target(
  'build_fonts3',
  input: 'src/Fonts/Roboto-Light.ttf',
  output: 'Roboto_Light.h',
  command: [bash, files('scripts/build_font.sh'), '@INPUT@', '@OUTPUT@'],
)

roboto_light = custom_target(
  'build_fonts4',
  input: 'src/Fonts/Icons.ttf',
  output: 'Icons.h',
  command: [bash, files('scripts/build_font.sh'), '@INPUT@', '@OUTPUT@'],
)

executable(
    'pengui',
    sources,
    roboto_regular,
    roboto_bold,
    roboto_light,
    dependencies: [
        glib,
        gio,
        libportal,
        gdk_pixbuf,
        gtk,
        glfw,
        imgui,
        glbinding
    ]
)
