#pragma once

#include <ZaapCLI.h>

#include "Entity.h"

#include <entity/Entity.h>
#include <maths\Vector3.h>
#include <maths\Matrix4.h>

namespace ZaapCLI
{
	ref class BaseEntity;
	
	public class EntityRedirecter : public zaap::Entity {
	private:
		gcroot<ZaapCLI::BaseEntity^> m_Owner;
	public:
		//Value Methods to excess the protected Values directly
		zaap::Vec3 getPositionValue();
		zaap::Vec3 getRotationValue();
		zaap::Vec3 getScaleValue();

		zaap::Vec3 setPositionValue(const zaap::Vec3& position);
		zaap::Vec3 setRotationValue(const zaap::Vec3& rotation);
		zaap::Vec3 setScaleValue(const zaap::Vec3& scale);

		EntityRedirecter(ZaapCLI::BaseEntity^ owner, zaap::graphics::Mesh *mesh,
			const zaap::Vec3& position = zaap::Vec3(0.0f, 0.0f, 0.0f),
			const zaap::Vec3& rotation = zaap::Vec3(0.0f, 0.0f, 0.0f),
			const zaap::Vec3& scale = zaap::Vec3(1.0f, 1.0f, 1.0f));
		EntityRedirecter(ZaapCLI::BaseEntity^ owner);

		//position
		void setPosition(const zaap::Vec3 &position) override;
		void callDefault_setPosition(const zaap::Vec3 &position);

		void increasePosition(const zaap::Vec3 &position) override;
		void callDefault_increasePosition(const zaap::Vec3 &position);

		//rotation
		void setRotation(const zaap::Vec3 &rotation) override;
		void callDefault_setRotation(const zaap::Vec3 &rotation);

		void increaseRotation(const zaap::Vec3 &rotation) override;
		void callDefault_increaseRotation(const zaap::Vec3 &rotation);

		//Scale
		void setScale(const float& scale) override;
		void callDefault_setScale(const float& scale);

		void setScale(const zaap::Vec3& scale) override;
		void callDefault_setScale(const zaap::Vec3& scale);

		void increaseScale(const float& scale) override;
		void callDefault_increaseScale(const float& scale);

		void increaseScale(const zaap::Vec3& scale) override;
		void callDefault_increaseScale(const zaap::Vec3& scale);

		// GameLoop util
		void update() override;
		void callDefault_update();
		void render() override;
		void callDefault_render();
	};

	public ref class BaseEntity : public Entity
	{
	private:
		EntityRedirecter* getInstance();
	protected:
		// __FILE__ is always defined
#ifdef __FILE__
		property Vector3^ m_Position {
			Vector3^ get()
			{
				return gcnew Vector3(&getInstance()->getPositionValue());
			}
			void set(Vector3^ position)
			{
				getInstance()->setPositionValue(*position->getHandle());
			}
		}
		property Vector3^ m_Rotation {
			Vector3^ get()
			{
				return gcnew Vector3(&getInstance()->getRotationValue());
			}
			void set(Vector3^ rotation)
			{
				getInstance()->setRotationValue(*rotation->getHandle());
			}
		}
		property Vector3^ m_Scale {
			Vector3^ get()
			{
				return gcnew Vector3(&getInstance()->getScaleValue());
			}
			void set(Vector3^ scale)
			{
				getInstance()->setScaleValue(*scale->getHandle());
			}
		}
#endif
	public:
		BaseEntity(Vector3^ position);
		BaseEntity(Vector3^ position, Vector3^ rotation);
		BaseEntity(Vector3^ position, Vector3^ rotation, Vector3^ scale);

		//position
		virtual void setPosition(Vector3^ position) override;
		virtual void increasePosition(Vector3^ position) override;

		//rotation
		virtual void setRotation(Vector3^ rotation) override;
		virtual void increaseRotation(Vector3^ rotation) override;

		//Scale
		virtual void setScale(float scale) override;
		virtual void setScale(Vector3^ scale) override;
		virtual void increaseScale(float scale) override;
		virtual void increaseScale(Vector3^ scale) override;

		// GameLoop util
		virtual void update() override;
		virtual void render() override;
	};
	
}
