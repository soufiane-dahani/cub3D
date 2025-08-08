# Texture Rendering in Cub3D

## Overview

Your cub3D now supports texture rendering on walls! Here's how it works:

## Key Components

### 1. Texture Structure (`t_texture`)

```c
typedef struct s_texture
{
    void *img;        // MLX image pointer
    char *addr;       // Image data address
    int width;        // Texture width
    int height;       // Texture height
    int bpp;          // Bits per pixel
    int line_len;     // Line length
    int endian;       // Endianness
} t_texture;
```

### 2. Texture Loading

- **File**: `raycasting/load_textures.c`
- Loads XPM files into texture structures
- Each wall direction has its own texture:
  - `no_texture` - North wall
  - `so_texture` - South wall
  - `we_texture` - West wall
  - `ea_texture` - East wall

### 3. Texture Utilities (`texture_utils.c`)

#### `get_texture_color(t_texture *texture, int x, int y)`

- Extracts color from texture at specific coordinates
- Returns black (0x000000) if coordinates are out of bounds

#### `get_wall_texture(t_game *game, int side, int step_x, int step_y)`

- Determines which texture to use based on wall direction
- Uses wall hit side and step direction to select appropriate texture

#### `get_wall_x(t_game *game, double ray_x, double ray_y, int side)`

- Calculates exact position where ray hit the wall
- Used to determine texture X coordinate

### 4. Enhanced Ray Casting

The `cast_ray()` function now:

1. **Detects Wall Side**: Determines if ray hit vertical or horizontal wall
2. **Calculates Texture Coordinates**:
   - `tex_x`: Horizontal position on texture
   - `tex_y`: Vertical position on texture (calculated per pixel)
3. **Applies Texture**: Samples texture color for each pixel
4. **Adds Shading**: Darkens horizontal walls for depth effect

## How Texture Mapping Works

### Step 1: Wall Hit Detection

```c
// Track previous position to determine wall side
double prev_ray_x = ray_x;
double prev_ray_y = ray_y;

// When wall is hit, determine which boundary was crossed
if (prev_map_x != map_x)
    side = 0; // Vertical wall
else
    side = 1; // Horizontal wall
```

### Step 2: Texture Selection

```c
t_texture *texture = get_wall_texture(game, side, step_x, step_y);
```

### Step 3: Texture Coordinate Calculation

```c
// Calculate where exactly on the wall the ray hit
double wall_x = get_wall_x(game, ray_x, ray_y, side);

// Convert to texture coordinate
int tex_x = (int)(wall_x * texture->width);

// Handle texture mirroring based on ray direction
if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
    tex_x = texture->width - tex_x - 1;
```

### Step 4: Vertical Texture Mapping

```c
// Calculate how much to increase texture coordinate per screen pixel
double step = (double)texture->height / wall_height;
double tex_pos = (draw_start - MAP_HEIGHT / 2 + wall_height / 2) * step;

// For each pixel in the wall stripe
for (int y = draw_start; y <= draw_end; y++)
{
    int tex_y = (int)tex_pos;
    int color = get_texture_color(texture, tex_x, tex_y);

    // Apply shading for depth
    if (side == 1)
        color = (color >> 1) & 0x7F7F7F; // Darken horizontal walls

    put_pixels(game, i, y, color);
    tex_pos += step;
}
```

## Visual Effects

### Depth Shading

- **Vertical walls**: Full brightness
- **Horizontal walls**: 50% brightness (darkened)
- Creates illusion of lighting and depth

### Texture Orientation

- Textures are automatically oriented correctly based on wall direction
- Prevents texture "mirroring" artifacts

## Usage

1. Ensure your `.cub` file has valid texture paths:

   ```
   NO ./drive/wall_1.xpm
   SO ./drive/wall_2.xpm
   WE ./drive/wall_3.xpm
   EA ./drive/wall_4.xpm
   ```

2. The textures will be automatically loaded and rendered when you run the game.

3. Move around with WASD keys and use mouse to look around - you'll see textured walls!

## Performance Notes

- Texture sampling is done per pixel, which is computationally intensive
- The current implementation prioritizes visual quality over performance
- For optimization, consider texture filtering or LOD (Level of Detail) techniques

## Troubleshooting

- **Black walls**: Check if texture files exist and are valid XPM format
- **Corrupted textures**: Verify texture paths in .cub file
- **Performance issues**: Consider reducing texture resolution or screen resolution

Your cub3D now renders beautiful textured walls! 🎮✨
