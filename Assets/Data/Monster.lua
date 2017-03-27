GameObject = {
	name = "Monster",
	controller = "MonsterController",
	count = 2.0,
	position = {-200.0,-100.0,0.0},
	AABB = {
		Center = {0,64.0,0.0},
		Extents = {64.0,64.0,0.0}
	},
	physicsbody = {
		mass = 1.0,
		drag = 1.0,
		forceMultiplier = 3000.0
	},
	rendersettings = {
		sprite = "Assets\\Sprites\\enemy.dds"
	}
}