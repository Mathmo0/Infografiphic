void Application::rotateFrameTrackBall(glm::vec2  v, glm::vec2 o)
{
	glm::vec3 v1 = projectOnSphere(v);
	glm::vec3 v2 = projectOnSphere(o);

	Frame *f = m_scene->getManipulatedNode()->frame();

	v1 = glm::normalize(v1);
	v2 = glm::normalize(v2);

	glm::vec3 rax = glm::normalize(glm::cross(v2, v1));
	if (!isnan(rax.x))
	{
		float angle = acos(glm::dot(v1, v2));
		rax = glm::normalize(m_scene->camera()->frame()->convertDirTo(rax, f));
		f->rotate(rax, (float)(M_PI*angle ));	

	}
}