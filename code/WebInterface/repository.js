
/**
 * test method
 * @returns {Promise<Array>}
 */
async function serverGet() {
    try {
        const result = await fetch('/api/get',
            {
                method: 'GET',
            }
        )
        return result.json()
    } catch (error) {
        console.log('serverGet - Error:', error)
        return []
    }
}
