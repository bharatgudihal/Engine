GameObject = {
	name = "Paddle",
	controller = "PlayerController",
	count = 1.0,
	isEnabled = "true",
	position = {0.0,-250.0,0.0},
	AABB = {
		Center = {0,10.0,0.0},
		Extents = {50.0,10.0,0.0}
	},
	physicsbody = {
		mass = 1.0,
		drag = 1.0,
		forceMultiplier = 40000.0
	},
	rendersettings = {
		sprite = "Assets\\Sprites\\player.dds"
	}
}