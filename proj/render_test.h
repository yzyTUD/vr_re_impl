#include <cgv/render/drawable.h>
#include <cgv/render/shader_program.h>
#include <cgv_gl/gl/gl.h>
#include <cgv/base/register.h>
#include <cgv/gui/trigger.h>
#include <cgv/gui/event_handler.h>
#include <cgv/gui/key_event.h>
#include <cgv/utils/ostream_printf.h>
#include <cgv/gui/provider.h>
#include <cgv/math/ftransform.h>
#include <cgv/media/illum/surface_material.h>

using namespace cgv::base;
using namespace cgv::reflect;
using namespace cgv::gui;
using namespace cgv::signal;
using namespace cgv::render;

class render_test :
	public base,    // base class of all to be registered classes
	public provider, // is derived from tacker, which is not necessary as base anymore
	public event_handler, // necessary to receive events
	public drawable // registers for drawing with opengl
{
private:
	cgv::render::box_render_style box_style;
	cgv::render::box_render_style sphere_style;
	std::vector<box3> random_boxes;
	std::vector<rgb> random_colors;
	std::vector<vec3> random_translations;
	std::vector<quat> random_rotations;
public:
public:
	/// initialize rotation angle
	render_test()
	{
		random_position_orientation_generator();
	}
	/// 
	void on_set(void* member_ptr)
	{
		update_member(member_ptr);
		post_redraw();
	}
	/// self reflection allows to change values in the config file
	bool self_reflect(reflection_handler& rh)
	{
		return true;
	}
	/// return the type name of the class derived from base
	std::string get_type_name() const
	{
		return "simple_cube";
	}
	/// show statistic information
	void stream_stats(std::ostream& os)
	{
	}
	/// show help information
	void stream_help(std::ostream& os)
	{
	}
	/// overload to handle events, return true if event was processed
	bool handle(event& e)
	{
		return true;
	}
	/// declare timer_event method to connect the shoot signal of the trigger
	void timer_event(double, double dt)
	{
	}
	/// setting the view transform yourself
	void draw(context& ctx)
	{
		
	}
	void random_position_orientation_generator() {
		float tw = 0.8f;
		float td = 0.8f;
		float th = 0.72f;
		float tW = 0.03f;
		int nr = 50;
		std::default_random_engine generator;
		std::uniform_real_distribution<float> distribution(0, 1);
		std::uniform_real_distribution<float> signed_distribution(-1, 1);
		for (size_t i = 0; i < nr; ++i) {
			float x = distribution(generator);
			float y = distribution(generator);
			vec3 extent(distribution(generator), distribution(generator), distribution(generator));
			extent += 0.01f;
			extent *= std::min(tw, td) * 0.1f;

			vec3 center(-0.5f * tw + x * tw, th + tW, -0.5f * td + y * td);
			random_boxes.push_back(box3(-0.5f * extent, 0.5f * extent));
			movable_box_colors.push_back(rgb(distribution(generator), distribution(generator), distribution(generator)));
			movable_box_translations.push_back(center);
			quat rot(signed_distribution(generator), signed_distribution(generator), signed_distribution(generator), signed_distribution(generator));
			rot.normalize();
			movable_box_rotations.push_back(rot);
		}
	}
	void render_random_boxes(context& ctx) {
		if (movable_boxes.size()) {
			cgv::render::box_renderer& renderer = cgv::render::ref_box_renderer(ctx);
			renderer.set_render_style(movable_style);
			renderer.set_box_array(ctx, random_boxes);
			renderer.set_color_array(ctx, movable_box_colors);
			renderer.set_translation_array(ctx, movable_box_translations);
			renderer.set_rotation_array(ctx, movable_box_rotations);
			renderer.render(ctx, 0, movable_boxes.size());
		}
	}
	void render_random_spheres(context& ctx) {
		if (movable_boxes.size()) {
			cgv::render::box_renderer& renderer = cgv::render::ref_box_renderer(ctx);
			renderer.set_render_style(movable_style);
			renderer.set_box_array(ctx, movable_boxes);
			renderer.set_color_array(ctx, movable_box_colors);
			renderer.set_translation_array(ctx, movable_box_translations);
			renderer.set_rotation_array(ctx, movable_box_rotations);
			renderer.render(ctx, 0, movable_boxes.size());
		}
	}
	/// overload the create gui method
	void create_gui()
	{

	}
};

