#version 330

// ============================================================
//  fragment.glsl
//
//  Logic-based shader effect (Requirement 5):
//  - When the player is at full health: normal rendering
//  - When health == 2/3: slight cool-blue tint on the map tiles
//  - When health == 1/3: red pulsing vignette around the edges
//    (darkness + red glow warning)
//  - When health == 0  : full red flash (game over imminent)
//
//  The effect uses if-statements to branch on u_health,
//  and contributes to the sci-fi theme by making the
//  "battle damage" feel tangible to the player.
// ============================================================

in  vec2      fragTexCoord;
in  vec4      fragColor;
out vec4      finalColor;

uniform sampler2D texture0;

// Set from main.cpp each frame:
uniform float u_health;    // 0.0 (dead) → 1.0 (full)
uniform float u_time;      // elapsed seconds, for pulsing

void main() {
    vec4 tex_color = texture(texture0, fragTexCoord) * fragColor;

    // ——— Screen-space vignette based on uv distance from centre ———
    // fragTexCoord is [0,1] in screen space when used as a post-process
    vec2  uv      = fragTexCoord;
    float dist    = length(uv - vec2(0.5, 0.5));  // 0.0 at centre, ~0.7 at corner

    // ——— Branch on health level ———
    if (u_health > 0.66) {
        // Full health: no effect
        finalColor = tex_color;

    } else if (u_health > 0.33) {
        // Medium health: subtle cold-blue desaturation tint
        float grey   = dot(tex_color.rgb, vec3(0.299, 0.587, 0.114));
        vec3  tinted = mix(tex_color.rgb, vec3(grey * 0.6, grey * 0.7, grey * 1.1), 0.25);
        // Soft dark vignette
        float vignette = 1.0 - smoothstep(0.35, 0.7, dist) * 0.4;
        finalColor = vec4(tinted * vignette, tex_color.a);

    } else if (u_health > 0.0) {
        // Low health: red pulsing vignette
        float pulse    = 0.5 + 0.5 * sin(u_time * 4.0);   // 0→1 at 2 Hz
        float vignette = smoothstep(0.25, 0.65, dist);     // 0 at centre, 1 at edge
        float red_amt  = vignette * pulse * 0.75;

        vec3  damaged  = tex_color.rgb;
        damaged.r      = min(1.0, damaged.r + red_amt);
        damaged.g      = damaged.g * (1.0 - red_amt * 0.5);
        damaged.b      = damaged.b * (1.0 - red_amt * 0.5);

        // Also darken the centre slightly
        float dark = 1.0 - vignette * 0.3;
        finalColor = vec4(damaged * dark, tex_color.a);

    } else {
        // Dead / zero health: full red flash
        float flash = 0.5 + 0.5 * sin(u_time * 10.0);
        finalColor  = vec4(flash, 0.0, 0.0, tex_color.a);
    }
}
