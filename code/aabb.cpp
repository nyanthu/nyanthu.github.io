struct Ray {
    Vec3 origin;
    Vec3 dir; // 正規化済み推奨
};

inline bool IntersectRayAABB(const Ray& ray, const AABB& box, float& tMinOut) {
    float tmin = (box.min.x - ray.origin.x) / ray.dir.x;
    float tmax = (box.max.x - ray.origin.x) / ray.dir.x;
    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (box.min.y - ray.origin.y) / ray.dir.y;
    float tymax = (box.max.y - ray.origin.y) / ray.dir.y;
    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) return false;

    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (box.min.z - ray.origin.z) / ray.dir.z;
    float tzmax = (box.max.z - ray.origin.z) / ray.dir.z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return false;

    if (tzmin > tmin) tmin = tzmin;

    tMinOut = tmin;
    return true;
}
