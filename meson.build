project('pengui', 'cpp', default_options: ['cpp_std=c++20'])

add_project_arguments(
  '-DGLFW_INCLUDE_NONE',
  language: 'cpp'
)

glib = dependency('glib-2.0')
gio = dependency('gio-2.0')
libportal = dependency('libportal', default_options: ['vapi=false', 'docs=false'])
gdk_pixbuf = dependency('gdk-pixbuf-2.0')
gtk = dependency('gtk4')
glfw = dependency('glfw3')
imgui = dependency('imgui', version: '>=1.92.6')
glbinding = dependency('glbinding', static: true)
tomlpp = dependency('tomlplusplus', static: true)

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
    'src/UI/Ruler.cpp',
    'src/Config/Config.cpp',
    'src/Storage/Storage.cpp',
    'src/Clipboard/Clipboard.h'
)

bash = find_program('bash', required: true)

find_program('xxd', required: true)
find_program('sed', required: true)
find_program('cp', required: true)
find_program('mkdir', required: true)

# foreach f : shaders
#   custom_target(
#     'shader_' + fs.name(fs.parent(f)) + '_' + fs.name(f),
#     input: f,
#     output: fs.name(fs.parent(f)) + '.' + fs.name(f) + '.generated',
#     command: [
#       bash,
#       files('scripts/copy_shader.sh'),
#       meson.project_build_root(),
#       fs.parent(f),
#       fs.name(f),
#     ],
#     build_by_default: true,
#   )
# endforeach

shader_glow_vert = custom_target(
  'shader_glow_vert',
  input: 'src/Shaders/Glow/vert.glsl',
  output: 'Glow_vert.h',
  command: [bash, files('scripts/build_shader.sh'), '@INPUT@', '@OUTPUT@'],
)

shader_glow_frag = custom_target(
  'shader_glow_frag',
  input: 'src/Shaders/Glow/frag.glsl',
  output: 'Glow_frag.h',
  command: [bash, files('scripts/build_shader.sh'), '@INPUT@', '@OUTPUT@'],
)

roboto_regular = custom_target(
  'roboto_regular',
  input: 'src/Fonts/Roboto-Regular.ttf',
  output: 'Roboto_Regular.h',
  command: [bash, files('scripts/build_font.sh'), '@INPUT@', '@OUTPUT@'],
)

icons = custom_target(
  'icons',
  input: 'src/Fonts/Icons.ttf',
  output: 'Icons.h',
  command: [bash, files('scripts/build_font.sh'), '@INPUT@', '@OUTPUT@'],
)

executable(
    'pengui',
    sources,
    roboto_regular,
    icons,
    shader_glow_vert,
    shader_glow_frag,
    dependencies: [
        glib,
        gio,
        libportal,
        gdk_pixbuf,
        gtk,
        glfw,
        imgui,
        glbinding,
        tomlpp
    ],
    install: true
)

install_data(
  files('data/net.kanashimo.pengui.desktop'),
  install_dir: join_paths(get_option('datadir'), 'applications')
)

install_subdir(
  'data/icons/hicolor',
  install_dir: join_paths(get_option('datadir'), 'icons')
)
