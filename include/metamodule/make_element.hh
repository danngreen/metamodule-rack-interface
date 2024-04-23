#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{

Element make_element_output(rack::app::SvgPort const *widget, BaseElement b);
Element make_element_input(rack::app::SvgPort const *widget, BaseElement b);
Element make_element(rack::app::SvgKnob *widget, BaseElement b);
Element make_element_slideswitch(rack::app::SvgSlider const *widget, BaseElement b);
Element make_element(rack::app::SvgSlider const *widget, BaseElement b);
Element make_element(rack::componentlibrary::Rogan const *widget, BaseElement b);
Element make_element(rack::app::SvgSwitch const *widget, BaseElement b);
Element make_element(rack::app::SvgScrew const *widget, BaseElement);
Element make_element(rack::widget::SvgWidget const *widget, BaseElement el);
Element make_element(rack::app::SliderKnob const *widget, BaseElement b);
Element make_element(rack::app::MultiLightWidget const *widget, BaseElement el);
Element make_mono_led_element(std::string_view image, rack::app::MultiLightWidget const *widget, BaseElement const &el);
Element make_dual_led_element(std::string_view image, rack::app::MultiLightWidget const *widget, BaseElement const &el);
Element make_rgb_led_element(std::string_view image, rack::app::MultiLightWidget const *widget, BaseElement const &el);
Element make_momentary_rgb(std::string_view image, BaseElement const &el);
Element make_latching_rgb(std::string_view image, BaseElement const &el);
Element make_latching_mono(std::string_view image, NVGcolor c, BaseElement const &el);
Element make_momentary_mono(std::string_view image, NVGcolor c, BaseElement const &el);

//
// Button with lights
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::VCVLightBezel<LightBaseT> const *widget, BaseElement el) {

	if (widget->light->getNumColors() == 1) {
		auto c = widget->light->baseColors[0];
		if (widget->momentary)
			return make_momentary_mono(widget->frames[0], c, el);
		else
			return make_latching_mono(widget->frames[0], c, el);
	}

	if (widget->light->getNumColors() == 3) {
		if (widget->momentary)
			return make_momentary_rgb(widget->frames[0], el);
		else
			return make_latching_rgb(widget->frames[0], el);
	}

	// printf("make_element(): Unknown VCVLightBezel\n");
	return NullElement{};
}

//
// SVG Light
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::TSvgLight<LightBaseT> const *widget, BaseElement el) {
	if (widget->getNumColors() == 1) {
		return make_mono_led_element(widget->sw->svg_filename, widget, el);
	}
	if (widget->getNumColors() == 2) {
		return make_dual_led_element(widget->sw->svg_filename, widget, el);
	}
	if (widget->getNumColors() == 3) {
		return make_rgb_led_element(widget->sw->svg_filename, widget, el);
	}

	// printf("Light widget not handled (%d colors)\n", widget->getNumColors());
	return NullElement{};
}

} // namespace MetaModule
