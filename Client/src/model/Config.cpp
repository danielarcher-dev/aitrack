#include "Config.h"

#include <QFileInfo>



ConfigData ConfigData::getGenericConfig()
{
	ConfigData conf = ConfigData();
	conf.ip = "";
	conf.port = 0;
	conf.camera_fov = 56.0;
	conf.prior_distance = .7;
	conf.show_video_feed = true;
	conf.selected_model = 0;
	conf.selected_camera = 0;
	conf.num_cameras_detected = 0;
	conf.video_width = -1;
	conf.video_height = -1;
	conf.video_fps = -1;
	conf.use_landmark_stab = true;
	conf.autocheck_updates = true;
	conf.tracking_shortcut_enabled = false;
	conf.x, conf.y, conf.z, conf.pitch, conf.yaw, conf.roll = 0;
	conf.cam_exposure = -1;
	conf.cam_gain = -1;
	conf.set_env_threads = true;
	conf.env_threads = 1;
	conf.set_num_threads = true;
	conf.num_threads = 1;
	conf.set_dynamic = true;
	conf.dynamic = 0;
	conf.head_scale_x = 1.0;
	conf.head_scale_y = 1.0;
	conf.head_scale_z = 1.0;

	return conf;
}


ConfigMgr::ConfigMgr(std::string ini_path):
	conf(ini_path.data(), QSettings::IniFormat)
{
	//Check if there was no file
	if(!QFileInfo(ini_path.data()).exists())
	{
		//Thre is no previous configuration so we set a default one
		ConfigData cnf_default = ConfigData::getGenericConfig();
		updateConfig(cnf_default);
	}
}

void ConfigMgr::updateConfig(const ConfigData& data)
{
	conf.setValue("ip", data.ip.data());
	conf.setValue("port", data.port);
	conf.setValue("camera_fov", data.camera_fov);
	conf.setValue("prior_distance", data.prior_distance);
	conf.setValue("video_feed", data.show_video_feed);
	conf.setValue("model", data.selected_model);
	conf.setValue("video_width", data.video_width);
	conf.setValue("video_height", data.video_height);
	conf.setValue("stabilize_landmarks", data.use_landmark_stab);
	conf.setValue("fps", data.video_fps);
	conf.setValue("cam_exposure", data.cam_exposure);
	conf.setValue("cam_gain", data.cam_gain);
	conf.setValue("selected_camera", data.selected_camera);
	conf.setValue("autocheck_updates", data.autocheck_updates);

	conf.setValue("set_env_threads", data.set_env_threads);
	conf.setValue("env_threads", data.env_threads);
	conf.setValue("set_num_threads", data.set_num_threads);
	conf.setValue("num_threads", data.num_threads);
	conf.setValue("set_dynamic", data.set_dynamic);
	conf.setValue("dynamic", data.dynamic);

	conf.setValue("head_3d_scale_x", data.head_scale_x);
	conf.setValue("head_3d_scale_y", data.head_scale_y);
	conf.setValue("head_3d_scale_z", data.head_scale_z);
	conf.setValue("tracking_shortcut_enabled", data.tracking_shortcut_enabled);

}

ConfigData ConfigMgr::getConfig()
{
	ConfigData c = ConfigData();
	c.ip = conf.value("ip", "").toString().toStdString();
	c.port = conf.value("port", 0).toInt();
	c.camera_fov = conf.value("camera_fov", 56.0).toDouble();
	c.prior_distance = conf.value("prior_distance", 0.0).toDouble();
	c.show_video_feed = conf.value("video_feed", true).toBool();
	c.use_landmark_stab = conf.value("stabilize_landmarks", true).toBool();
	c.selected_model = conf.value("model", 0).toInt();
	c.selected_camera = conf.value("selected_camera", 0).toInt();
	c.video_width = conf.value("video_width", 640).toInt();
	c.video_height = conf.value("video_height", 480).toInt();
	c.video_fps = conf.value("fps", 30).toInt();
	c.cam_exposure= conf.value("cam_exposure", -1).toInt();
	c.cam_gain = conf.value("cam_gain", -1).toInt();
	c.autocheck_updates = conf.value("autocheck_updates", 1).toBool();

	c.set_env_threads = conf.value("set_env_threads", true).toBool();
	c.env_threads = conf.value("env_threads", 1).toInt();
	c.set_num_threads = conf.value("set_num_threads", true).toBool();
	c.num_threads = conf.value("num_threads", 1).toInt();
	c.set_dynamic = conf.value("set_dynamic", true).toBool();
	c.dynamic = conf.value("dynamic", 0).toInt();

	c.head_scale_x = conf.value("head_3d_scale_x", 1.0).toDouble();
	c.head_scale_y = conf.value("head_3d_scale_y", 1.0).toDouble();
	c.head_scale_z = conf.value("head_3d_scale_z", 1.0).toDouble();
	c.tracking_shortcut_enabled= conf.value("tracking_shortcut_enabled", false).toBool();

	return c;
}

